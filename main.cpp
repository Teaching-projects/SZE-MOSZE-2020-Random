#include <iostream>
#include <time.h>

struct Mob {
  Mob(const std::string& n, const float& h, const float& d) : name(n), health(h), damage(d) {}
  ~Mob() {}

  std::string name = "";
  float health = 0;
  float damage = 0;
};

std::ostream& operator<<(std::ostream& os, const Mob& mob) {
  os << mob.name << "(HP:" << mob.health << ", DMG:" << mob.damage << ")";
  return os;
}

int random(const int& from, const int& to) { //includes endpoints
  if (to > from) {
    return (rand() % ((to - from) + 1)) + from;
  }
  else {
    return from;
  }
}

void attack(const Mob& from, Mob& to) {
  std::cout << "\n" << from << " attacks " << to << std::endl;
  to.health -= from.damage;
  std::cout << "Damage dealt: " << from.damage << std::endl;
}

int main() {
  srand(time(NULL));

  Mob m1("David", random(100, 200), random(30, 50));
  Mob m2("Goliath", random(300, 750), random(5, 10));

  std::cout << m1 << "\n" << m2 << std::endl;

  while ((m1.health > 0) && (m2.health > 0)) {
    attack(m1, m2);
    attack(m2, m1);
  }

  if (m1.health <= 0) {
    std::cout << "\n" << m2 << " wins!" << std::endl;
  }
  else {
    std::cout << "\n" << m1 << " wins!" << std::endl;
  }

  return 0;
}
