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
public:
  struct Damage {
    Damage() : physical(0), magical(0) {}
    Damage(const float& physical, const float& magical)
      : physical(physical), magical(magical) {}

    float physical = 0;
    float magical = 0;

    Damage operator+(const Damage& other) const;
    Damage& operator+=(const Damage& other);
    Damage& operator*=(const float& other);

    int total(const int& defense = 0) const;
  };

protected:
  std::string name = "";      ///< Name of the monster.
  float healthPoints = 0;     ///< Current health of the monster.
  Damage damage;              ///< Damage, that the monster deals to its opponents.
  float attackCooldown = 0;   ///< The time it takes to reload the attack.
  float cooldownState = 0;    ///< Current state of the attack reloading.
  float defense = 0;

  /**
   * \brief Function for dealing damage.
   * \param monster the reference of the Monster type, that the damage is dealt to
   * \param damage the amount of the damage
   *
   * Lowers the amount of health points of the given Monster with the amount of the damage parameter.
   */
  void sufferDamage(Monster& monster, const Damage& damage);

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
  Monster(const std::string& name, const float& healthPoints, const Damage& damage, const float& attackCooldown, const float& defense) :
    name(name), healthPoints(healthPoints), damage(damage), attackCooldown(attackCooldown), cooldownState(attackCooldown), defense(defense) {}

  //functions

  /**
   * \brief Elapse time.
   * \param t the time to be elapsed
   *
   * Modifies the class variables depending on the value of the t parameter.
   */
  void elapseTime(const float& t);

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
  Damage getDamage() const { return damage; }

  /// Getter for the attackCooldown variable.
  float getAttackCooldown() const { return attackCooldown; }

  float getDefense() const { return defense; }
};

#endif
