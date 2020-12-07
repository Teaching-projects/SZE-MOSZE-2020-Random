#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"

class Renderer {
public:
  Renderer() {}
  virtual void render(const Game& game) const = 0;
};

#endif
