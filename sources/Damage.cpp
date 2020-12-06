#include "Monster.h"

Monster::Damage Monster::Damage::operator+(const Damage& other) const {
  return Damage(physical + other.physical, magical + other.magical);
}

Monster::Damage& Monster::Damage::operator+=(const Damage& other) {
  physical += other.physical;
  magical += other.magical;
  return *this;
}

Monster::Damage& Monster::Damage::operator*=(const float& other) {
  physical *= other;
  magical *= other;
  return *this;
}

int Monster::Damage::total(const int& defense) const {
  int temp = physical - defense;
  if (temp < 0) { temp = 0; }
  return temp + magical;
}
