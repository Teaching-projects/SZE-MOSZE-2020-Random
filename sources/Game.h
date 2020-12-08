#ifndef GAME_H
#define GAME_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "Renderer.h"

class Renderer;

/**
 * \class Game
 * \brief Class for managing the game.
 *
 * This is a class that manages the main game loop and game functionalities.
 *
 * \author LengyHELL
 * \version 1.1
 * \date 2020/12/08 15:45
 */
class Game {
public:

  /**
   * \class Game::OccupiedException
   *
   * This is an exception class used by the Game class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/02 14:39
   */
  class OccupiedException : public std::exception {
  public:
    ~OccupiedException() throw() {}
    const char* what() const throw() { return "Position is occupied."; }
  };

  /**
   * \class Game::AlreadyHasHeroException
   *
   * This is an exception class used by the Game class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/02 14:39
   */
  class AlreadyHasHeroException : public std::exception {
  public:
    ~AlreadyHasHeroException() throw() {}
    const char* what() const throw() { return "Hero already defined."; }
  };

  /**
   * \class Game::AlreadyHasUnitsException
   *
   * This is an exception class used by the Game class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/02 14:39
   */
  class AlreadyHasUnitsException : public std::exception {
  public:
    ~AlreadyHasUnitsException() throw() {}
    const char* what() const throw() { return "Units already defined."; }
  };

  /**
   * \class Game::NotInitializedException
   *
   * This is an exception class used by the Game class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/02 14:39
   */
  class NotInitializedException : public std::exception {
  public:
    ~NotInitializedException() throw() {}
    const char* what() const throw() { return "Game elements are not initialized."; }
  };

  /**
   * \class Game::GameAlreadyStartedException
   *
   * This is an exception class used by the Game class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/02 14:39
   */
  class GameAlreadyStartedException : public std::exception {
  public:
    ~GameAlreadyStartedException() throw() {}
    const char* what() const throw() { return "The game already started."; }
  };

  /**
   * \struct Game::GameMonster
   *
   * This class represents a Monster with a specific positon on the map.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/07 14:16
   */
  struct GameMonster {
    Monster monster;  ///< The represented Monster.
    int x = -1;       ///< The Monster's x position.
    int y = -1;       ///< The Monster's y position.
  };

  /**
   * \struct Game::GameHero
   *
   * This class represents a Hero with a specific positon on the map.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/07 14:16
   */
  struct GameHero {
    Hero hero;        ///< The represented Hero.
    int x = -1;       ///< The Hero's x position.
    int y = -1;       ///< The Hero's y position.
  };

protected:
  bool running = false;         ///< Indicates if the game is running.
  std::string wallTexture = ""; ///< Stores the texture for the wall, used when drawing as an SVG file.
  std::string freeTexture = ""; ///< Stores the texture fot the free path, used when drawing as an SVG file.

private:
  Map gameMap;
  GameHero gameHero;
  std::vector<GameMonster> gameMonsters;
  std::list<Renderer*> renderers;

public:
  /// Default constructor, creates an empty game.
  Game() {}

  /// Default destructor, clears the attached renderers.
  ~Game();

  /// Constructor that loads the game with the given Map.
  explicit Game(const std::string& mapfilename) : gameMap(Map(mapfilename)) {}

  /**
   * \brief Sets the map.
   * \param map the Map to be set for the Game object
   * \exception Game::GameAlreadyStartedException is thrown when the Map is changed after the game has been started
   * \exception Game::AlreadyHasUnitsException is thrown when units have been already placed on the map
   *
   * This function changes the current map to the one given as a parameter.
   */
  void setMap(const Map& map);

  /**
   * \brief Places a Hero.
   * \param hero the Hero to be placed
   * \param x the placed Hero's x position
   * \param y the placed Hero's y position
   * \exception Game::GameAlreadyStartedException is thrown when the Hero is placed after the game has been started
   * \exception Map::WrongIndexException is thrown when the position of the Hero is not valid
   * \exception Game::OccupiedException is thrown when the position of the Hero is on the wall
   * \exception Game::AlreadyHasHeroException is thrown when a Hero is placed after another Hero is already put down
   *
   * This function places a Hero to the given position.
   */
  void putHero(const Hero& hero, int x, int y);

  /**
   * \brief Places a Monster.
   * \param monster the Monster to be placed
   * \param x the placed Monster's x position
   * \param y the placed Monster's y position
   * \exception Game::GameAlreadyStartedException is thrown when the Monster is placed after the game has been started
   * \exception Map::WrongIndexException is thrown when the position of the Monster is not valid
   * \exception Game::OccupiedException is thrown when the position of the Monster is on the wall
   *
   * This function places a Monster to the given position.
   */
  void putMonster(const Monster& monster, int x, int y);

  /**
   * \brief Attaching renderer.
   * \param renderer the Renderer that is attached to the game
   *
   * This function registers one or more renderer to the game, and uses it to draw the game state in every game cycle.
   */
  void registerRenderer(Renderer* renderer);

  /**
   * \brief Running the game.
   * \param is the std::istream that the game commands are read from
   * \exception Game::GameAlreadyStartedException is thrown when the function is run while the game is still running
   * \exception Game::NotInitializedException is thrown when the game is not set up properly when it is started
   *
   * This function starts and runs the game process.
   */
  void run(std::istream& is = std::cin);

  /// Checks if the hero is set.
  bool hasHero() const { return (gameHero.x >= 0) && (gameHero.y >= 0); }

  /// Returns the map that is set for the game value.
  Map getMap() const { return gameMap; }

  /// Returns the hero that is set for the game.
  GameHero getHero() const { return gameHero; }

  /// Returns the monsters that are set for the game.
  std::vector<GameMonster> getMonsters() const { return gameMonsters; }

  /// Returns the string of the wall texture.
  std::string getWallTexture() const { return wallTexture; }

  /// Returns the string of the free path texture.
  std::string getFreeTexture() const { return freeTexture; }
};

#endif
