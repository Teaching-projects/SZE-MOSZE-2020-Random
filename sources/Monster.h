#ifndef MONSTER_H
#define MONSTER_H

#include <string>

/**
 * \class Monster
 * \brief Main class for monsters.
 *
 * Defines the parameters and actions of the monsters.
 *
 * \author LengyHELL
 * \version 1.1
 * \date 2020/11/01 17:02
 */
class Monster {
protected:
  std::string name = "";      ///< Name of the monster.
  float healthPoints = 0;     ///< Current health of the monster.
  float damage = 0;           ///< Damage, that the monster deals to its opponents.
  float attackCooldown = 0;   ///< The time it takes to reload the attack.
  float cooldownState = 0;    ///< Current state of the attack reloading.

  /**
   * \brief Function for dealing damage.
   * \param monster the reference of the Monster type, that the damage is dealt to
   * \param damage the amount of the damage
   *
   * Lowers the amount of health points of the given Monster with the amount of the damage parameter.
   */
  void sufferDamage(Monster& monster, const float& damage);

  /**
   * \brief Elapse time.
   * \param monster the Monster type that the elapsed time is applied to
   * \param t the time to be elapsed
   *
   * Modifies the class variables depending on the value of the t parameter.
   */
  void elapseTime(Monster& monster, const float& t);

  /**
   * \brief Cooldown reset.
   *
   * Resets the state of the cooldown.
   */
  void resetCooldown();

public:
  //constructor, destructor

  /// Default constructor.
  Monster() {}

  /// Constructor with parameters for the class.
  Monster(const std::string& name, const float& healthPoints, const float& damage, const float& attackCooldown) :
    name(name), healthPoints(healthPoints), damage(damage), attackCooldown(attackCooldown), cooldownState(attackCooldown) {}

  //functions

  /**
   * \brief Check if is alive.
   * \return bool
   *
   * Checks if the monster is alive, depending on its health points.
   */
  bool isAlive() const { return healthPoints > 0; }

  /**
   * \brief Check if able to hit.
   * \return bool
   *
   * Checks if the monster is able to attack, depending on its cooldown state.
   */
  bool canHit() const { return cooldownState <= 0; }

  /**
   * \brief JSON parser.
   * \param filename string that describes the file to be opened
   * \return Monster class
   * \exception JSON::ParseException is thrown on syntax and reading errors, from the JSON class
   *
   * Parses a simple JSON file and returns its values as a Monster object.
   */
  static Monster parse(const std::string& filename);

  /**
   * \brief Attack function.
   * \param other a Monster type object
   *
   * Performs an attack on the Monster type given as a parameter.
   */
  virtual void attack(Monster& other);

  //getters

  /// Getter for the name variable.
  std::string getName() const { return name; }

  /// Getter for the healthPoints variable.
  float getHealthPoints() const { return healthPoints; }

  /// Getter for the damage variable.
  float getDamage() const { return damage; }

  /// Getter for the attackCooldown variable.
  float getAttackCooldown() const { return attackCooldown; }
};

#endif
