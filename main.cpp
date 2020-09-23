#include <iostream>
#include "unit.hpp"

int main(int argc, char** argv) {

  Unit m1, m2;

  try {
    m1.parse_unit(argv[1]);
    m2.parse_unit(argv[2]);
  }
  catch(const UnitException& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  while ((m1.get_health() > 0) && (m2.get_health() > 0)) {
    m1.attack(m2);
    m2.attack(m1);
  }

  if (m1.get_health() <= 0) {
    std::cout << m2.get_name() << " wins! Remaining HP: " << m2.get_health() << std::endl;
  }
  else {
    std::cout << m1.get_name() << " wins! Remaining HP: " << m1.get_health() << std::endl;
  }

  return 0;
}
