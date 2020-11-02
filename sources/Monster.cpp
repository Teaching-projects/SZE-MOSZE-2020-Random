#include "Monster.h"
#include "JSON.h"

void Monster::sufferDamage(Monster& monster, const float& damage) {
  monster.healthPoints -= damage;
  if (monster.healthPoints < 0) { monster.healthPoints = 0; }
}

void Monster::elapseTime(Monster& monster, const float& t) {
  monster.cooldownState -= t;
}

void Monster::resetCooldown() {
  cooldownState += attackCooldown;
  if (cooldownState > attackCooldown) {
    cooldownState = attackCooldown;
  }
}

void Monster::attack(Monster& other) {
  if (isAlive() && canHit()) {
    resetCooldown();
    sufferDamage(other, damage);
  }
}

Monster Monster::parse(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  return Monster(
    file.get<std::string>("name"),
    file.get<int>("health_points"),
    file.get<int>("damage"),
    file.get<float>("attack_cooldown")
  );
}
