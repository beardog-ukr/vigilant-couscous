#include "GameMapNode.h"

using namespace cocos2d;
using namespace std;

static const string mapFileName = "maps/m02.tmx";

// --- --------------------------------------------------------------------

GameMapNode::GameMapNode() {
  log("%s: here", __func__);
}

// --- --------------------------------------------------------------------

GameMapNode::~GameMapNode() {
  log("%s: here", __func__);
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
  TMXTiledMap *const mapNode =  TMXTiledMap::create(mapFileName);

  if (mapNode == nullptr)  {
    log("%s:failed to load tiled map from %s.", __func__, mapFileName.c_str());
    return false;
  }

  setContentSize(mapNode->getContentSize());

  mapNode->setAnchorPoint(Vec2(0, 0));
  mapNode->setPosition(Vec2(0, 0));
  addChild(mapNode);

  // --- set ap for the node
  setAnchorPoint(Vec2(0.5, 0.5));

  return true;
}

// --- --------------------------------------------------------------------
