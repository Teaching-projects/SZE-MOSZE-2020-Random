#ifndef HERO_H
#define HERO_H

#include "Monster.h"

/**
 * \class Hero
 * \brief Derived class from Monster.
 *
 * Defines the parameters and actions of the heroes, and adds extra abilites.
 *
 * \author LengyHELL
 * \version 1.1
 * \date 2020/11/01 17:26
 */
class Hero : public Monster {
  float baseHealthPoints = 0;             ///< Maximum health that the hero can have.

  float experiencePerLevel = 0;           ///< The amount of experience needed for reaching the next level.
  float experienceState = 0;              ///< The current amount of experience the hero has.
  float healthPointBonusPerLevel = 0;     ///< The extra health points the hero obtains from leveling up.
  float damageBonusPerLevel = 0;          ///< The extra damage the hero obtains from leveling up.
  float cooldownMultiplierPerLevel = 0;   ///< Modifies the attack cooldown when leveling up.
  float level = 0;                        ///< The actual level of the hero.

public:
  //constructor, destructor

  /// Default constructor
  Hero() {}

  /// Constructor with parameters for the class.
  Hero(const std::string& name, const float& healthPoints, const float& damage, const float& attackCooldown, const float& experiencePerLevel,
    const float& healthPointBonusPerLevel, const float& damageBonusPerLevel, const float& cooldownMultiplierPerLevel) :
    Monster(name, healthPoints, damage, attackCooldown), baseHealthPoints(healthPoints), experiencePerLevel(experiencePerLevel),
    experienceState(0), healthPointBonusPerLevel(healthPointBonusPerLevel), damageBonusPerLevel(damageBonusPerLevel),
    cooldownMultiplierPerLevel(cooldownMultiplierPerLevel), level(1) {}


  //functions

  /**
   * \brief JSON parser.
   * \param filename string that describes the file to be opened
   * \return Hero class
   * \exception JSON::ParseException is thrown on syntax and reading errors, from the JSON class
   *
   * Parses a simple JSON file and returns its values as a Hero object.
   */
  static Hero parse(const std::string& filename);

  /**
   * \brief Attack function.
   * \param other a Monster type object
   *
   * Performs an attack on the Monster type given as a parameter, overloads the base class's attack function.
   */
  void attack(Monster& other) override;

  /**
   * \brief Fight with another Monster type.
   * \param other the other Monster type to fight with
   *
   * Simulates a fight between the Hero and an other Monster type object, until one of them loses.
   */
  void fightTilDeath(Monster& other);

  /// Getter for the baseHealthPoints variable.
  float getMaxHealthPoints() const { return baseHealthPoints; }

  /// Getter for the level variable.
  float getLevel() const { return level; }
};

#endif
