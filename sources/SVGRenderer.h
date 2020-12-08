#ifndef SVG_RENDERER_H
#define SVG_RENDERER_H

#include "Renderer.h"

class SVGRenderer : public Renderer {
protected:
  std::string filename;

public:
  SVGRenderer(const std::string& filename) : filename(filename) {}
  virtual void render(const Game& game) const override = 0;
};

#endif
