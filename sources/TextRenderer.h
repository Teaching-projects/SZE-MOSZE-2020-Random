#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Renderer.h"
#include <iostream>

class TextRenderer : public Renderer {
protected:
  std::ostream* outputStream;

public:
  TextRenderer() : outputStream(&std::cout) {}
  virtual void render(const Game& game) const = 0;
  void setOutputStream(std::ostream& os = std::cout) { outputStream = &os; }
};

#endif
