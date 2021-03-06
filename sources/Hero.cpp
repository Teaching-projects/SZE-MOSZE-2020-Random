#include "Hero.h"
#include "JSON.h"
#include <cmath>

Hero Hero::parse(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  Damage dmg, bonusDmg;
  float lightPerLevel = 1;
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

  if (file.count("light_radius_per_level")) {
    lightPerLevel = file.get<int>("light_radius_per_level");
  }

  return Hero(
    file.get<std::string>("name"),
    file.get<int>("base_health_points"),
    dmg,
    file.get<float>("base_attack_cooldown"),
    file.get<int>("base_defense"),
    file.get<std::string>("texture"),
    file.get<int>("experience_per_level"),
    file.get<int>("health_point_bonus_per_level"),
    bonusDmg,
    file.get<float>("cooldown_multiplier_per_level"),
    file.get<int>("defense_bonus_per_level"),
    file.get<int>("base_light_radius"),
    lightPerLevel
  );
}

void Hero::attack(Monster& other) {
  if (isAlive() && canHit()) {
    if (other.getHealthPoints() >= damage.total(other.getDefense())) {
      experienceState += damage.total(other.getDefense());
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
      defense += defenseBonusPerLevel;
      lightRadius += lightRadiusPerLevel;
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
