#include "Hero.h"
#include "JSON.h"
#include <cmath>

Hero Hero::parse(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  return Hero(
    file.get<std::string>("name"),
    file.get<int>("base_health_points"),
    file.get<int>("base_damage"),
    file.get<float>("base_attack_cooldown"),
    file.get<int>("experience_per_level"),
    file.get<int>("health_point_bonus_per_level"),
    file.get<int>("damage_bonus_per_level"),
    file.get<float>("cooldown_multiplier_per_level")
  );
}

void Hero::attack(Monster& other) {
  if (isAlive() && canHit()) {
    if (other.getHealthPoints() >= damage) {
      experienceState += damage;
    }
    else {
      experienceState += other.getHealthPoints();
    }
    sufferDamage(other, damage);
    while (experienceState >= experiencePerLevel) {
      level += 1;
      experienceState -= experiencePerLevel;
      baseHealthPoints += healthPointBonusPerLevel;
      healthPoints = baseHealthPoints;
      damage += damageBonusPerLevel;
      attackCooldown *= cooldownMultiplierPerLevel;
    }
    resetCooldown();
  }
}

void Hero::fightTilDeath(Monster& other) {
  while (isAlive() && other.isAlive()) {
    attack(other);
    other.attack(*this);
    elapseTime(*this, 0.1);
    elapseTime(other, 0.1);
  }
}
