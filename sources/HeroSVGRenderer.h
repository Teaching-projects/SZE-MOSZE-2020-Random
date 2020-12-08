#ifndef HERO_SVG_RENDERER_H
#define HERO_SVG_RENDERER_H

#include "SVGRenderer.h"

/**
 * \class HeroSVGRenderer
 * \brief Class for rendering game states to SVG images.
 *
 * Renders a game in SVG format at the hero's viewpoint for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 16:11
 */
class HeroSVGRenderer : public SVGRenderer {
public:
  /// Constructor that sets the filename.
  explicit HeroSVGRenderer(const std::string& filename) : SVGRenderer(filename) {}

  void render(const Game& game) const override;
};

#endif
