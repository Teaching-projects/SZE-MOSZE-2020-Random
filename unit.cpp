#include "unit.hpp"
#include "json.hpp"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
  os << unit.get_name() << "(HP:" << unit.get_health() << ", DMG:" << unit.get_damage() << ")";
  return os;
}

Unit Unit::parse_unit(const std::string& filename) {
  Json test;
  test.parse_file(filename);
  return Unit(test.get_string("name"), test.get_int("hp"), test.get_int("dmg"));
}

void Unit::attack(Unit& other) const {
  if (health > 0) {
    //std::cout << std::endl << name << " attacks " << other.get_name() << std::endl;
    other.suffer_damage(damage);
    //std::cout << *this << std::endl << other << std::endl;
  }
}

void Unit::suffer_damage(const float& damage) {
  health -= damage;
}
