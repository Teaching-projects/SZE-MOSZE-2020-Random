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
class Hero : public Monster {
  float baseHealthPoints = 0;   ///< Maximum health that the player can have.

  float experiencePerLevel = 0; ///< The amount of experience needed for reaching the next level.
  float experienceState = 0;       ///< The current amount of experience the player has.
  float healthPointBonusPerLevel = 0;
  float damageBonusPerLevel = 0;
  float cooldownMultiplierPerLevel = 0;
  float level = 0;    ///< The actual level of the player.

public:
  //constructor, destructor

  Hero() {}

  Hero(const std::string& name, const float& healthPoints, const float& damage, const float& attackCooldown, const float& experiencePerLevel,
    const float& healthPointBonusPerLevel, const float& damageBonusPerLevel, const float& cooldownMultiplierPerLevel) :
    Monster(name, healthPoints, damage, attackCooldown), baseHealthPoints(healthPoints), experiencePerLevel(experiencePerLevel),
    experienceState(0), healthPointBonusPerLevel(healthPointBonusPerLevel), damageBonusPerLevel(damageBonusPerLevel),
    cooldownMultiplierPerLevel(cooldownMultiplierPerLevel), level(1) {}


  //functions

  static Hero parse(const std::string& filename);

  /**
   * \brief Attack function.
   * \param other a Unit object
   *
   * Performs an attack on the Unit given as a parameter, overloads the base class's attack function.
   */
  void attack(Monster& other);

  void fightTilDeath(Monster& other);

  /// Getter for the max_hp variable.
  float getMaxHealthPoints() const { return baseHealthPoints; }

  /// Getter for the level variable.
  float getLevel() const { return level; }
};

#endif
