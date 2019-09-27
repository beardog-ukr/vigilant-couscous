#include "MainGameScene.h"
#include "game/GameMapNode.h"


#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;

static const string backgroundImageFileName = "ui/Background_Large3.png";
static const string spiderImageFileName     = "spider/sliced002.png";
static const string warriorImageFileName    = "warrior/knight_iso_char_slice_left_1.png";

// --- --------------------------------------------------------------------

Scene * MainGameScene::createScene()
{
  return MainGameScene::create();
}

// --- --------------------------------------------------------------------

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
  //////////////////////////////
  // 1. super init first
  if (!Scene::init())
  {
    return false;
  }

  // --- constructor things go here


  // --- background
  if (!initBackground()) {
    return false;
  }

  // --- keyboard
  if (!initTiledMap()) {
    return false;
  }

  // --- keyboard
  if (!initDebug()) {
    return false;
  }

  // --- keyboard
  if (!initKeyboardProcessing()) {
    return false;
  }

  // --- finally
  return true;
}

// --- --------------------------------------------------------------------

bool MainGameScene::initBackground() {
  log("%s: here", __func__);
  Sprite *sprite = Sprite::create(backgroundImageFileName);

  if (sprite == nullptr) {
    log("%s: failed to load %s file", __func__, backgroundImageFileName.c_str());
    return false;
  }

  // --- else

  // position the sprite on the center of the screen
  const Size visibleSize = Director::getInstance()->getVisibleSize();
  const Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

  // add the sprite as a child to this layer
  addChild(sprite, 0);

  return true;
}

// --- --------------------------------------------------------------------

bool MainGameScene::initDebug() {
  log("%s: here", __func__);
  Sprite *sprite = Sprite::create(warriorImageFileName);

  if (sprite == nullptr) {
    log("%s: failed to load %s file", __func__, warriorImageFileName.c_str());
    return false;
  }

  // --- else

  // position the sprite on the center of the screen
  const Size visibleSize = Director::getInstance()->getVisibleSize();
  const Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x - 110,
                           visibleSize.height / 2 + origin.y));

  // add the sprite as a child to this layer
  addChild(sprite, 0);

  sprite = Sprite::create(spiderImageFileName);

  if (sprite == nullptr) {
    log("%s: failed to load %s file", __func__, spiderImageFileName.c_str());
    return false;
  }

  // --- else
  sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + 120,
                           visibleSize.height / 2 + origin.y));

  // add the sprite as a child to this layer
  addChild(sprite, 0);


  auto closeItem = MenuItemImage::create(
    "CloseNormal.png",
    "CloseSelected.png",
    CC_CALLBACK_1(MainGameScene::menuCloseCallback, this));

  if ((closeItem == nullptr) ||
      (closeItem->getContentSize().width <= 0) ||
      (closeItem->getContentSize().height <= 0))
  {
    log("%s: failed to load 'CloseNormal.png CloseSelected.png' file", __func__);
  }
  else
  {
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));
  }

  // create menu, it's an autorelease object
  auto menu = Menu::create(closeItem, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu);

  return true;
}

// --- --------------------------------------------------------------------

bool MainGameScene::initKeyboardProcessing() {
  log("%s: here", __func__);

  return true;
}

// --- --------------------------------------------------------------------

bool MainGameScene::initTiledMap() {
  mapNode =  GameMapNode::create();

  if (mapNode == nullptr)  {
    log("%s:failed to load tiled map.", __func__);
    return false;
  }

  const Size visibleSize = Director::getInstance()->getVisibleSize();
  const Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  // mapNode->setAnchorPoint(Vec2(0.5, 0.5));
  mapNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  addChild(mapNode);

  return true;
}

// --- --------------------------------------------------------------------

void MainGameScene::menuCloseCallback(Ref *pSender)
{
  // Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();

  /*To navigate back to native iOS screen(if present) without quitting the
     application  ,do not use Director::getInstance()->end() as given
     above,instead trigger a custom event created in RootViewController.mm as
     below*/

  // EventCustom customEndEvent("game_scene_close_event");
  // _eventDispatcher->dispatchEvent(&customEndEvent);
}
