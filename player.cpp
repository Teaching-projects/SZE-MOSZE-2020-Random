#include "player.hpp"
#include "math.h"

Player& Player::operator=(const Unit& unit) {
  name = unit.get_name();
  health = unit.get_health();
  damage = unit.get_damage();
  max_hp = unit.get_health();
  return *this;
}

void Player::attack(Unit& other) {
  if (health > 0) {
    other.suffer_damage(damage);
    xp += damage;
    while (xp >= max_xp) {
      level += 1;
      xp -= max_xp;
      max_hp *= 1.1;
      max_hp = floor(max_hp * 1.1);
      damage = floor(damage * 1.1);
      health = max_hp;
    }
  }
}
