#ifndef PLAYER_H
#define PLAYER_H

#include "unit.hpp"

class Player : public Unit {
  float max_hp = 0;
  float max_xp = 100;
  float xp = 0;
  float level = 0;

public:
  Player() : Unit("", 0, 0), max_hp(0), max_xp(100), xp(0), level(0) {}
  Player(const std::string& n, const float& h, const float& d) : Unit(n, h, d), max_hp(h), max_xp(100), xp(0), level(0) {}

  Player& operator=(const Unit& unit);
  void attack(Unit& other);

  float get_max_health() const { return max_hp; }
  float get_max_xp() const { return max_xp; }
  float get_xp() const { return xp; }
  float get_level() const { return level; }

};

#endif
