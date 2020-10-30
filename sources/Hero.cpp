#include "Hero.h"
#include <cmath>

Player& Player::operator=(const Unit& unit) {
  name = unit.get_name();
  health = unit.get_health();
  damage = unit.get_damage();
  cd = unit.get_cd();

  max_hp = unit.get_health();
  max_cd = unit.get_max_cd();
  return *this;
}

void Player::attack(Unit& other) {
  if ((health > 0) && (cd <= 0)) {
    if (other.get_health() >= damage) {
      xp += damage;
    }
    else {
      xp += other.get_health();
    }
    suffer_damage(other, damage);
    while (xp >= max_xp) {
      level += 1;
      xp -= max_xp;
      max_hp = round(max_hp * 1.1);
      damage = round(damage * 1.1);
      max_cd = max_cd * 0.9;
      health = max_hp;
    }
    cd += max_cd;
  }
}
