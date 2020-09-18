#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>

class Unit {
  std::string name = "";
  float health = 0;
  float damage = 0;

public:
  Unit(const std::string& n, const float& h, const float& d) : name(n), health(h), damage(d) {}
  //~Unit() {}

  //operator overload
  friend std::ostream& operator<<(std::ostream& os, const Unit& unit);

  //functions
  void attack(Unit& other) const;
  void suffer_damage(const float& damage);

  //getters
  std::string get_name() const { return name; }
  float get_health() const { return health; }
  float get_damage() const { return damage; }
};

#endif
