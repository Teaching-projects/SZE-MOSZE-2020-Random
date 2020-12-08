#ifndef HERO_TEXT_RENDERER_H
#define HERO_TEXT_RENDERER_H

#include "TextRenderer.h"

class HeroTextRenderer : public TextRenderer {
public:
  HeroTextRenderer(std::ostream& os = std::cout) : TextRenderer(os) {}

  void render(const Game& game) const override;
};

#endif