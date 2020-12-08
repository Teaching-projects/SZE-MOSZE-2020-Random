#ifndef OBSERVER_SVG_RENDERER_H
#define OBSERVER_SVG_RENDERER_H

#include "SVGRenderer.h"

/**
 * \class ObserverSVGRenderer
 * \brief Class for rendering game states to SVG images.
 *
 * Renders a game in SVG format at an observer viewpoint for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 16:09
 */
class ObserverSVGRenderer : public SVGRenderer {
public:

  /// Constructor that sets the filename.
  explicit ObserverSVGRenderer(const std::string& filename) : SVGRenderer(filename) {}

  void render(const Game& game) const override;
};

#endif
