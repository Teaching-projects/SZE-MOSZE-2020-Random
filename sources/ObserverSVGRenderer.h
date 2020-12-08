#ifndef OBSERVER_SVG_RENDERER_H
#define OBSERVER_SVG_RENDERER_H

#include "SVGRenderer.h"

class ObserverSVGRenderer : public SVGRenderer {
public:
  ObserverSVGRenderer(const std::string& filename) : SVGRenderer(filename) {}

  void render(const Game& game) const override;
};

#endif
