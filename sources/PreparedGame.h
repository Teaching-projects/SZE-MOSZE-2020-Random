#ifndef PREPAREDGAME_H
#define PREPAREDGAME_H

#include "Game.h"

/**
 * \class PreparedGame
 * \brief Derived class from Game.
 *
 * This is a class that manages the main game loop and game functionalities, and set up by a given configuration file.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/06 16:36
 */
class PreparedGame : public Game {
  using Game::setMap;
  using Game::putHero;
  using Game::putMonster;
  using Game::hasHero;

public:

  /**
   * \brief PreparedGame constructor.
   * \param filename the configuration file, that the game is loaded from
   * \exception JSON::ParseException is thrown if an error occurs while reading the given JSON file
   *
   * Opens the file given as parameter and loads the map and units to the game.
   */
  explicit PreparedGame(const std::string& filename);
};

#endif
