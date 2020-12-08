#ifndef OBSERVER_TEXT_RENDERER_H
#define OBSERVER_TEXT_RENDERER_H

#include "TextRenderer.h"

class ObserverTextRenderer : public TextRenderer {
public:
  ObserverTextRenderer(std::ostream& os = std::cout) : TextRenderer(os) {}

  void render(const Game& game) const override;
};

#endif
