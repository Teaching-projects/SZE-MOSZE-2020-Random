#ifndef MONSTER_H
#define MONSTER_H

#include <string>

/**
 * \class Unit
 * \brief Main class for units.
 *
 * Defines the parameters and actions of the fighters.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/10/15 10:33
 */
class Monster {
protected:
  std::string name = "";      ///< Name of the unit.
  float healthPoints = 0;     ///< Health of the unit.
  float damage = 0;           ///< Damage, that the unit deals to its opponents.
  float attackCooldown = 0;   ///< The time it takes to reload the attack.
  float cooldownState = 0;    ///< Current state of the attack reloading.

  /**
   * \brief Function for dealing damage.
   * \param unit the reference of the unit, that the damage is dealt to
   * \param damage the amount of the damage
   *
   * Lowers the amount of hp with the amount of the damage parameter.
   */
  void sufferDamage(Monster& monster, const float& damage);

  /**
   * \brief Elapse time.
   * \param t the time to be elapsed
   *
   * Modifies the class variables depending on the value of the t parameter.
   */
  void elapseTime(Monster& monster, const float& t);

  void resetCooldown();

public:
  //constructor, destructor

  Monster() {}

  Monster(const std::string& name, const float& healthPoints, const float& damage, const float& attackCooldown) :
    name(name), healthPoints(healthPoints), damage(damage), attackCooldown(attackCooldown), cooldownState(attackCooldown) {}

  //functions

  bool isAlive() const { return healthPoints > 0; }

  bool canHit() const { return cooldownState <= 0; }

  /**
   * \brief JSON parser.
   * \param filename string that describes the file to be opened
   * \return Unit class
   * \exception UnitException is thrown on syntax and reading errors
   *
   * Parses a simple JSON file and puts its values into an Unit object.
   */
  static Monster parse(const std::string& filename);

  /**
   * \brief Attack function.
   * \param other a Unit object
   *
   * Performs an attack on the Unit given as a parameter.
   */
  virtual void attack(Monster& other);

  //getters

  /// Getter for the name variable.
  std::string getName() const { return name; }

  /// Getter for the health variable.
  float getHealthPoints() const { return healthPoints; }

  /// Getter for the damage variable.
  float getDamage() const { return damage; }

  /// Getter for the cd variable.
  float getAttackCooldown() const { return attackCooldown; }
};

#endif
