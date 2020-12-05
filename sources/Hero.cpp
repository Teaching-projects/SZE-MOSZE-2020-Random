#include "Hero.h"
#include "JSON.h"
#include <cmath>

Hero Hero::parse(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  Damage dmg, bonusDmg;
  if (file.count("base_damage")) {
    dmg.physical = file.get<int>("base_damage");
    bonusDmg.physical = file.get<int>("damage_bonus_per_level");
    if (file.count("base_magical_damage")) {
      dmg.magical = file.get<int>("base_magical_damage");
      bonusDmg.magical = file.get<int>("magical_damage_bonus_per_level");
    }
  }
  else {
    dmg.magical = file.get<int>("base_magical_damage");
    bonusDmg.magical = file.get<int>("magical_damage_bonus_per_level");
  }

  return Hero(
    file.get<std::string>("name"),
    file.get<int>("base_health_points"),
    dmg,
    file.get<float>("base_attack_cooldown"),
    file.get<int>("experience_per_level"),
    file.get<int>("health_point_bonus_per_level"),
    bonusDmg,
    file.get<float>("cooldown_multiplier_per_level")
  );
}

void Hero::attack(Monster& other) {
  if (isAlive() && canHit()) {
    if (other.getHealthPoints() >= damage.total()) {
      experienceState += damage.total();
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
    elapseTime(0.1);
    other.elapseTime(0.1);
  }
}
