#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"

/**
 * \class Game
 *
 * This is a class that manages the main game loop and game functionalities.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/02 14:39
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

private:
  struct GameMonster {
    Monster monster;
    int x = -1;
    int y = -1;
  };
  struct GameHero {
    Hero hero;
    int x = -1;
    int y = -1;
  };

  Map gameMap;
  GameHero gameHero;
  std::vector<GameMonster> gameMonsters;

  bool running = false;

  void draw() const;

public:
  /// Default constructor, creates an empty game.
  Game() {}

  /// Constructor that loads the game with the given Map.
  Game(const std::string& mapfilename) : gameMap(Map(mapfilename)) {}

  /**
   * \brief Sets the map.
   * \param map the Map to be set for the Game object
   * \exception Game::GameAlreadyStartedException is thrown when the Map is changed after the game has been started
   * \exception Game::OccupiedException is thrown when the position of the Hero is not valid
   *
   * This function changes the current map to the one given as a parameter.
   */
  void setMap(Map map);

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
  void putHero(Hero hero, int x, int y);

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
  void putMonster(Monster monster, int x, int y);

  /**
   * \brief Running the game.
   * \exception Game::GameAlreadyStartedException is thrown when the function is run while the game is still running
   * \exception Game::NotInitializedException is thrown when the game is not set up properly when it is started
   *
   * This function starts the game process.
   */
  void run();
};

#endif
