#include "Monster.h"
#include "JSON.h"

void Monster::sufferDamage(Monster& monster, const Damage& damage) {
  monster.healthPoints -= damage.total(monster.getDefense());
  if (monster.healthPoints < 0) { monster.healthPoints = 0; }
}

void Monster::resetCooldown() {
  cooldownState += attackCooldown;
  if (cooldownState > attackCooldown) {
    cooldownState = attackCooldown;
  }
}

void Monster::elapseTime(const float& t) {
  cooldownState -= t;
}

void Monster::attack(Monster& other) {
  if (isAlive() && canHit()) {
    resetCooldown();
    sufferDamage(other, damage);
  }
}

Monster Monster::parse(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  Damage dmg;
  if (file.count("damage")) {
    dmg.physical = file.get<int>("damage");
    if (file.count("magical_damage")) {
      dmg.magical = file.get<int>("magical_damage");
    }
  }
  else {
    dmg.magical = file.get<int>("magical_damage");
  }

  return Monster(
    file.get<std::string>("name"),
    file.get<int>("health_points"),
    dmg,
    file.get<float>("attack_cooldown"),
    file.get<int>("defense"),
    file.get<std::string>("texture")
  );
}
