#ifndef HERO_SVG_RENDERER_H
#define HERO_SVG_RENDERER_H

#include "SVGRenderer.h"

class HeroSVGRenderer : public SVGRenderer {
public:
  HeroSVGRenderer(const std::string& filename) : SVGRenderer(filename) {}

  void render(const Game& game) const override;
};

#endif
