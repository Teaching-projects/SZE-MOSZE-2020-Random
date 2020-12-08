#ifndef OBSERVER_TEXT_RENDERER_H
#define OBSERVER_TEXT_RENDERER_H

#include "TextRenderer.h"

/**
 * \class ObserverTextRenderer
 * \brief Class for rendering game states to text.
 *
 * Renders a game in text format at an observer viewpoint for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 16:12
 */
class ObserverTextRenderer : public TextRenderer {
public:

  /// Constructor that sets the output stream.
  explicit ObserverTextRenderer(std::ostream& os = std::cout) : TextRenderer(os) {}

  void render(const Game& game) const override;
};

#endif
