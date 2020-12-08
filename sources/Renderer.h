#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"

#include <string>

class Game;

/**
 * \class Renderer
 * \brief Class for rendering game states.
 *
 * Renders a game in some visual format for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 15:47
 */
class Renderer {
public:
  /// Default constructor.
  Renderer() {}

  /// Default destructor.
  virtual ~Renderer() {}

  /**
   * \brief Render function.
   * \param game the Game object to be rendered
   *
   * Renders a given Game object for the user in some visual format.
   */
  virtual void render(const Game& game) const = 0;
};

#endif
