#ifndef UNIT_H
#define UNIT_H

#include <iostream>
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
class Unit {
protected:
  std::string name = "";  ///< Name of the unit.
  float health = 0;       ///< Health of the unit.
  float damage = 0;       ///< Damage, that the unit deals to its opponents.
  float max_cd = 0;       ///< The time it takes to reload the attack.
  float cd = 0;           ///< Current state of the attack reloading.

  /**
   * \brief Function for dealing damage.
   * \param unit the reference of the unit, that the damage is dealt to
   * \param damage the amount of the damage
   *
   * Lowers the amount of hp with the amount of the damage parameter.
   */
  void suffer_damage(Unit& unit, const float& damage);

public:
  /// Default constructor without parameters, gives default values to the class variables.
  Unit() : name(""), health(0), damage(0), max_cd(0), cd(0) {}

  /// Unit constructor, gives the parameter values to the class variables.
  Unit(const std::string& n, const float& h, const float& d, const float& cd) : name(n), health(h), damage(d), max_cd(cd), cd(0) {}

  //~Unit() {}

  //operator overload

  /**
   * \brief Overload of << operator.
   * \param os an std::ostream that the text is put into
   * \param unit a Unit object that is written into the stream
   * \return std::ostream
   *
   * Writes the contents of the Unit class variables with overloading the << operator.
   */
  friend std::ostream& operator<<(std::ostream& os, const Unit& unit);

  //functions

  /**
   * \brief JSON parser.
   * \param filename string that describes the file to be opened
   * \return Unit class
   * \exception UnitException is thrown on syntax and reading errors
   *
   * Parses a simple JSON file and puts its values into an Unit object.
   */
  static Unit parse_unit(const std::string& filename);

  /**
   * \brief Attack function.
   * \param other a Unit object
   *
   * Performs an attack on the Unit given as a parameter.
   */
  virtual void attack(Unit& other);

  /**
   * \brief Elapse time.
   * \param t the time to be elapsed
   *
   * Modifies the class variables depending on the value of the t parameter.
   */
  void elapse_time(const float& t);

  //getters

  /// Getter for the name variable.
  std::string get_name() const { return name; }

  /// Getter for the health variable.
  float get_health() const { return health; }

  /// Getter for the damage variable.
  float get_damage() const { return damage; }

  /// Getter for the cd variable.
  float get_cd() const { return cd; }

  /// Getter for the max_cd variable.
  float get_max_cd() const { return max_cd; }
};

#endif
