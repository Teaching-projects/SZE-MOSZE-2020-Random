#ifndef SVG_RENDERER_H
#define SVG_RENDERER_H

#include "Renderer.h"

/**
 * \class SVGRenderer
 * \brief Class for rendering game states to SVG images.
 *
 * Renders a game in SVG format for the user.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/08 15:50
 */
class SVGRenderer : public Renderer {
protected:
  std::string filename;   ///< The name of the SVG file to be rendered to.

public:
  /// Constructor that sets the filename.
  SVGRenderer(const std::string& filename) : filename(filename) {}

  /// Default destructor.
  virtual ~SVGRenderer() {}
  
  virtual void render(const Game& game) const override = 0;
};

#endif
