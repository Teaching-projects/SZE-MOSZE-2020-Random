#include <iostream>
#include "unit.hpp"

int main(int argc, char** argv) {

  if (argc != 7) {
    std::cerr << "Invalid arguments!" << std::endl;
    return 1;
  }

  float hp1 = (float)strtod(argv[2], NULL);
  float hp2 = (float)strtod(argv[5], NULL);
  float dmg1 = (float)strtod(argv[3], NULL);
  float dmg2 = (float)strtod(argv[6], NULL);

  if ((hp1 <= 0) || (hp2 <= 0) || (dmg1 <= 0) || (dmg2 <= 0)) {
    std::cerr << "Invalid arguments!" << std::endl;
    return 1;
  }

  Unit m1(argv[1], hp1, dmg1);
  Unit m2(argv[4], hp2, dmg2);

  std::cout << m1 << " vs. " << m2 << std::endl;

  while ((m1.get_health() > 0) && (m2.get_health() > 0)) {
    m1.attack(m2);
    m2.attack(m1);
  }

  if (m1.get_health() <= 0) {
    std::cout << std::endl << m2 << " wins!" << std::endl;
  }
  else {
    std::cout << std::endl << m1 << " wins!" << std::endl;
  }

  return 0;
}
