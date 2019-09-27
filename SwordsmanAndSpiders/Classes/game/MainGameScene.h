#pragma once

#include "cocos2d.h"

class GameMapNode;

class MainGameScene : public cocos2d::Scene {
public:

  static cocos2d::Scene* createScene();

  virtual bool           init();

  // a selector callback
  void                   menuCloseCallback(cocos2d::Ref *pSender);

  // implement the "static create()" method manually
  CREATE_FUNC(MainGameScene);

protected:

  GameMapNode *mapNode;

  bool initBackground();

  bool initKeyboardProcessing();
  bool initTiledMap();

  bool initDebug();
};
