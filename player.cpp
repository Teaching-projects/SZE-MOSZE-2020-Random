#include "player.hpp"
#include <cmath>

Player& Player::operator=(const Unit& unit) {
  name = unit.get_name();
  health = unit.get_health();
  damage = unit.get_damage();
  max_hp = unit.get_health();
  return *this;
}

void Player::attack(Unit& other) {
  if (health > 0) {
    if (other.get_health() >= damage) {
      xp += damage;
    }
    else {
      xp += other.get_health();
    }
    other.suffer_damage(damage);
    while (xp >= max_xp) {
      level += 1;
      xp -= max_xp;
      max_hp = round(max_hp * 1.1);
      damage = round(damage * 1.1);
      health = max_hp;
    }
  }
}
