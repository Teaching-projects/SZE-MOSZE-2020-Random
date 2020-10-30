#ifndef HERO_H
#define HERO_H

#include "Monster.h"

/**
 * \class Player
 * \brief Derived class from Unit.
 *
 * Defines the parameters and actions of the fighters, and adds extra levelup functionality.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/10/19 20:17
 */
class Player : public Unit {
  float max_hp = 0;   ///< Maximum health that the player can have.
  float max_xp = 100; ///< The amount of experience needed for reaching the next level.
  float xp = 0;       ///< The current amount of experience the player has.
  float level = 0;    ///< The actual level of the player.

public:
  /// Default constructor.
  Player() : max_hp(0), max_xp(100), xp(0), level(0) {}

  /// Player constructor, gives the parameter values to the class variables.
  Player(const std::string& n, const float& h, const float& d, const float& cd) : Unit(n, h, d, cd), max_hp(h), max_xp(100), xp(0), level(0) {}

  /**
   * \brief Overload of == operator.
   * \param unit a Unit object that is copied into the Player object
   * \return Player
   *
   * Copies the variable data from a Unit base object to the corresponding Player object.
   */
  Player& operator=(const Unit& unit);

  /**
   * \brief Attack function.
   * \param other a Unit object
   *
   * Performs an attack on the Unit given as a parameter, overloads the base class's attack function.
   */
  void attack(Unit& other);

  /// Getter for the max_hp variable.
  float get_max_health() const { return max_hp; }

  /// Getter for the max_xp variable.
  float get_max_xp() const { return max_xp; }

  /// Getter for the xp variable.
  float get_xp() const { return xp; }

  /// Getter for the level variable.
  float get_level() const { return level; }

};

#endif
