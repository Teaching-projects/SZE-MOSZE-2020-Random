#include <iostream>
#include "unit.hpp"

int main(int argc, char** argv) {

  Unit m1("David", 150, 50);
  Unit m2("Goliath", 500, 5);

  std::cout << m1 << " vs. " << m2 << std::endl;

  while ((m1.get_health() > 0) && (m2.get_health() > 0)) {
    m1.attack(m2);
    m2.attack(m1);
  }

  if (m1.get_health() <= 0) {
    std::cout << "\n" << m2 << " wins!" << std::endl;
  }
  else {
    std::cout << "\n" << m1 << " wins!" << std::endl;
  }

  return 0;
}
