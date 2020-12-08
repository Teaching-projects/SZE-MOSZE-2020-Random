#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"

#include <string>

class Game;

class Renderer {
public:
  Renderer() {}
  virtual ~Renderer() {}
  virtual void render(const Game& game) const = 0;
};

#endif
