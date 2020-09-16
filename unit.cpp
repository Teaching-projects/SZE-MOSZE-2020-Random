#include "unit.hpp"

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
  os << unit.get_name() << "(HP:" << unit.get_health() << ", DMG:" << unit.get_damage() << ")";
  return os;
}

void Unit::attack(Unit& other) const {
  if (health > 0) {
    std::cout << std::endl << name << " attacks " << other.get_name() << std::endl;
    other.suffer_damage(damage);
    std::cout << *this << std::endl << other << std::endl;
  }
}

void Unit::suffer_damage(const float& damage) {
  health -= damage;
}
