#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;

static const string backgroundImageFileName = "ui/Background_Large3.png";

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

bool MainGameScene::initKeyboardProcessing() {
  log("%s: here", __func__);

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
