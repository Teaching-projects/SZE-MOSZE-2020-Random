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
 * \version 1.2
 * \date 2020/12/05 16:35
 */
class Monster {
public:

  /**
   * \struct Damage
   *
   * Represents the amount damage that the monster can deal.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/05 18:02
   */
  struct Damage {

    /// Default constructor.
    Damage() : physical(0), magical(0) {}

    /// Constructor with parameters for each variable.
    Damage(const float& physical, const float& magical)
      : physical(physical), magical(magical) {}

    float physical = 0;     ///< Physical damage, its affected by defense.
    float magical = 0;      ///< Magical damage.

    /**
     * \brief Overloaded + operator.
     * \param other
     * \return Damage
     *
     * The values are added together by damage type and returned.
     */
    Damage operator+(const Damage& other) const;

    /**
     * \brief Overloaded += operator.
     * \param other the Damage that the values are increased by
     * \return Damage&
     *
     * The other values are added to the current values and returned as a reference.
     */
    Damage& operator+=(const Damage& other);

    /**
     * \brief Overloaded *= operator.
     * \param other the float value that the values are multiplied by
     * \return Damage&
     *
     * The values are multiplied by the other parameter and returned as a reference.
     */
    Damage& operator*=(const float& other);

    /**
     * \brief Total damage.
     * \param defense the amount of defense considered while calculating the total damage
     * \return int
     *
     * Calculates the total damage with all damage types including the given defense.
     */
    int total(const int& defense = 0) const;
  };

protected:
  std::string name = "";      ///< Name of the monster.
  float healthPoints = 0;     ///< Current health of the monster.
  Damage damage;              ///< Damage, that the monster deals to its opponents.
  float attackCooldown = 0;   ///< The time it takes to reload the attack.
  float cooldownState = 0;    ///< Current state of the attack reloading.
  float defense = 0;          ///< The amount of physical damage that can be avoided.
  std::string texture = "";   ///< The texture used for SVG drawing.

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

  /// Default constructor.
  Monster() {}

  /// Constructor with parameters for the class.
  Monster(const std::string& name, const float& healthPoints, const Damage& damage,
    const float& attackCooldown, const float& defense, const std::string& texture) :
    name(name), healthPoints(healthPoints), damage(damage), attackCooldown(attackCooldown),
    cooldownState(attackCooldown), defense(defense), texture(texture) {}

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

  /// Getter for the name variable.
  std::string getName() const { return name; }

  /// Getter for the healthPoints variable.
  float getHealthPoints() const { return healthPoints; }

  /// Getter for the damage variable.
  Damage getDamage() const { return damage; }

  /// Getter for the attackCooldown variable.
  float getAttackCooldown() const { return attackCooldown; }

  /// Getter for the defense variable.
  float getDefense() const { return defense; }

  /// Getter for the texture variable.
  std::string getTexture() const { return texture; }
};

#endif
