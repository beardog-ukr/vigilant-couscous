#include "GameMapNode.h"
#include "common/SixCatsLogger.h"
#include "game/MetaTileCode.h"

using namespace cocos2d;
using namespace std;

static const string mapFileName = "maps/m02.tmx";
const string metaLayerName      = "meta_info";

// --- --------------------------------------------------------------------

GameMapNode::GameMapNode() {
  shared_ptr<SixCatsLogger> tmp_c6(new SixCatsLogger(SixCatsLogger::Debug));
  c6 = tmp_c6;

  baseScreenPos = Vec2(-1, -1);

  c6->t(__c6_MN__, "here");
}

// --- --------------------------------------------------------------------

GameMapNode::~GameMapNode() {
  c6->t(__c6_MN__, "here");
}

// --- --------------------------------------------------------------------

GameMapNode * GameMapNode::create() {
  GameMapNode *result = new (std::nothrow) GameMapNode();

  // Note, init()  here is inherited from Node
  if (result && result->initGameMapNode()) {
    result->autorelease();
  }
  else {
    CC_SAFE_DELETE(result); // deletes and sets ptr to NULL
  }
  return result;
}

// --- --------------------------------------------------------------------

bool GameMapNode::initGameMapNode() {
  // --- load map
  TMXTiledMap *const mapNode =  TMXTiledMap::create(mapFileName);

  if (mapNode == nullptr)  {
    log("%s:failed to load tiled map from %s.", __func__, mapFileName.c_str());
    return false;
  }

  setContentSize(mapNode->getContentSize());

  mapNode->setAnchorPoint(Vec2(0, 0));
  mapNode->setPosition(Vec2(0, 0));
  addChild(mapNode);

  // --- hide "meta" layer  --------------------
  TMXLayer *layer = mapNode->getLayer(metaLayerName);

  if (layer != nullptr) {
    layer->setVisible(false);
  }
  else {
    c6->c(__c6_MN__, [metaLayerName, mapFileName](ostringstream& ss) {
      ss << "Warning: " << metaLayerName << "layer not found in " << mapFileName;
    });
  }

  // --- search for start points
  if (!searchForStartingPoints(mapNode)) {
    return false;
  }

  // --- set ap for the node
  setAnchorPoint(Vec2(0.5, 0.5));

  return true;
}

// --- --------------------------------------------------------------------

bool GameMapNode::searchForStartingPoints(cocos2d::TMXTiledMap *mapNode) {
  bool result = true;

  TMXLayer *const metaLayer = mapNode->getLayer(metaLayerName);

  if (metaLayer == nullptr) {
    return false;
  }

  // perform Search
  bool warriorPosFound = false;
  bool spiderPosFound  = true;

  const Size mapSize = mapNode->getMapSize();

  for (int tileX = 0; tileX < mapSize.width; tileX++) {
    for (int tileY = 0; tileY < mapSize.height; tileY++) {
      const int   tileGid = metaLayer->getTileGIDAt(Vec2(tileX, tileY));
      const Value prop    = mapNode->getPropertiesForGID(tileGid);

      if (prop.isNull()) {
        continue;
      }

      const ValueMap vm   = prop.asValueMap();
      const auto     frez = vm.find("MetaTileCode");

      if (frez == vm.end()) {
        continue;
      }

      const int metaCode = frez->second.asInt();

      switch (metaCode) {
      case MTC_SAS_WARRIOR_START:

        warriorPosFound = true;
        warriorStartX   = tileX;
        warriorStartY   = mapSize.height - tileY - 1;


        c6->d(__c6_MN__, [this](ostringstream& ss) {
          ss << "Detected warrior start point as "
             << this->warriorStartX << ":" << this->warriorStartY;
        });

        break;

      case MTC_SAS_SPIDER_START:

        spiderPosFound = true;
        spiderStartX   = tileX;
        spiderStartY   = mapSize.height - tileY - 1;
        break;

        // Note there is no suitable default action here
        // default:
      }
    }
  }

  if (!warriorPosFound) {
    c6->w("Failed to find warrior pos");
  }

  if (!spiderPosFound) {
    c6->w("Failed to find spider pos");
  }

  return warriorPosFound && spiderPosFound;
}

// --- --------------------------------------------------------------------

Vec2 GameMapNode::getWarriorStartPos() {
  Vec2 result = calcScreenPosFromCorneredPos(warriorStartX, warriorStartY);

  // const int supposedTileSize = 32;

  // result.x = basePoint.x + (warriorStartX + 1) * supposedTileSize;
  // result.y = basePoint.y + (warriorStartY + 1) * supposedTileSize;

  // c6->d(__c6_MN__, [result](ostringstream& ss) {
  //   ss << "Result warrior start is " << result.x << ":" << result.y;
  // });

  return result;
}

// --- --------------------------------------------------------------------

Vec2 GameMapNode::getSpiderStartPos() {
  Vec2 result = calcScreenPosFromCorneredPos(spiderStartX, spiderStartY);

  return result;
}

// --- --------------------------------------------------------------------

Vec2 GameMapNode::calcScreenPosFromCorneredPos(const int cx, const int cy) {
  if ((baseScreenPos.x < 0) && (baseScreenPos.y < 0)) {
    const Vec2 cPos   = getPosition();
    const Vec2 cAnc   = getAnchorPoint();
    const Size ccSize = getContentSize();

    baseScreenPos = Vec2(cPos.x - (ccSize.width * cAnc.x), cPos.y - (ccSize.height * cAnc.y));

    c6->d(__c6_MN__, [this](ostringstream& ss) {
      ss << "Base point is as "
         << this->baseScreenPos.x << ":" << this->baseScreenPos.y;
    });
  }

  const int supposedTileSize = 32;

  Vec2 result(baseScreenPos.x + (cx + 1) * supposedTileSize,
              baseScreenPos.y + (cy + 1) * supposedTileSize);


  // result.x = ;
  // result.y = ;

  return result;
}

// --- --------------------------------------------------------------------
