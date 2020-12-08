#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Renderer.h"
#include <iostream>

/**
 * \class TextRenderer
 * \brief Class for rendering game states to text.
 *
 * Renders a game in text format for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 15:53
 */
class TextRenderer : public Renderer {
protected:
  std::ostream* outputStream;   ///< The output stream that the text is put into.

public:
  /// Constructor that sets the output stream.
  TextRenderer(std::ostream& os = std::cout) { setOutputStream(os); }

  /// Default destructor.
  virtual ~TextRenderer() {}

  virtual void render(const Game& game) const override = 0;

  /// Function that sets the output stream to the given parameter.
  void setOutputStream(std::ostream& os = std::cout) { outputStream = &os; }
};

#endif
