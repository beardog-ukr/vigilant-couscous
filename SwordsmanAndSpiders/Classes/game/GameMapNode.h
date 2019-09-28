#pragma once

#include "cocos2d.h"

// #include <string>
class SixCatsLogger;

class GameMapNode : public cocos2d::Node {
public:

  GameMapNode();
  virtual ~GameMapNode();

  /**
   * Creates a node with tiled map
   *
   * Loads liled map and gets some info from it.
   *
   * * @param name of map (TBD).
   */
  static GameMapNode* create();

  cocos2d::Vec2       getWarriorStartPos();
  cocos2d::Vec2       getSpiderStartPos();

protected:

  std::shared_ptr<SixCatsLogger>c6;

  bool initGameMapNode();

  int warriorStartX;
  int warriorStartY;

  int spiderStartX;
  int spiderStartY;

  cocos2d::Vec2 baseScreenPos;
  cocos2d::Vec2 calcScreenPosFromCorneredPos(const int cx,
                                             const int cy);

  bool          searchForStartingPoints(cocos2d::TMXTiledMap *mapNode);
};
