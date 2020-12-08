#ifndef HERO_TEXT_RENDERER_H
#define HERO_TEXT_RENDERER_H

#include "TextRenderer.h"

/**
 * \class HeroTextRenderer
 * \brief Class for rendering game states to text.
 *
 * Renders a game in text format at the hero's viewpoint for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 16:12
 */
class HeroTextRenderer : public TextRenderer {
public:

  /// Constructor that sets the output stream.
  HeroTextRenderer(std::ostream& os = std::cout) : TextRenderer(os) {}

  void render(const Game& game) const override;
};

#endif
