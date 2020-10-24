#include "unit.hpp"
#include "json.hpp"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
  os << unit.get_name() << "(HP:" << unit.get_health() << ", DMG:" << unit.get_damage() << ")";
  return os;
}

Unit Unit::parse_unit(const std::string& filename) {
  Json file;
  file.parse_file(filename);
  return Unit(file.get_string("name"), file.get_int("hp"), file.get_int("dmg"), file.get_float("cd"));
}

void Unit::attack(Unit& other) {
  if ((health > 0) && (cd <= 0)) {
    cd += max_cd;
    suffer_damage(other, damage);
  }
}

void Unit::elapse_time(const float& t) {
  cd -= t;
}

void Unit::suffer_damage(Unit& unit, const float& damage) {
  unit.health -= damage;
  if (unit.health < 0) { unit.health = 0; }
}
