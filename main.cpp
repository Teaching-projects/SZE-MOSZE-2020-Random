#include <iostream>
#include "unit.hpp"

int main(int argc, char** argv) {

  //Unit m1("David", random(100, 200), random(30, 50));
  //Unit m2("Goliath", random(300, 750), random(5, 10));

  std::cout << m1 << "\n" << m2 << std::endl;

  while ((m1.health > 0) && (m2.health > 0)) {
    m1.attack(m2);
    m2.attack(m1);
  }

  if (m1.health <= 0) {
    std::cout << "\n" << m2 << " wins!" << std::endl;
  }
  else {
    std::cout << "\n" << m1 << " wins!" << std::endl;
  }

  return 0;
}
