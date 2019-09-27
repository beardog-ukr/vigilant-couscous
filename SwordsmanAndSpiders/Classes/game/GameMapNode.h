#pragma once

#include "cocos2d.h"

// #include <string>

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

protected:

  bool initGameMapNode();
};
