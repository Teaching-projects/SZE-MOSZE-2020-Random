#include "unit.hpp"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
  os << unit.get_name() << "(HP:" << unit.get_health() << ", DMG:" << unit.get_damage() << ")";
  return os;
}

Unit Unit::parse_unit(const std::string& filename) {
  Unit ret;
  std::ifstream file(filename);

  if (file.is_open()) {
    char c;
    std::string sep = "{,}";
    std::string data = "";
    bool in_quotes = false;
    while(file.get(c)) {
      if (c == '\"') {
        in_quotes = !in_quotes;
      }
      if (!isspace(c) || in_quotes) { data += c; }
    }

    if (data.front() != '{') { throw UnitException("Invalid syntax!"); }

    int begin = data.find_first_of(sep) + 1;
    int end = 0;
    bool close = false;
    while (end < (int)data.size() - 1) {
      if (close) { throw UnitException("Invalid syntax!"); }

      end = data.find_first_of(sep, begin);

      if (end == -1) { throw UnitException("Invalid syntax!"); }

      std::string line = data.substr(begin, end - begin);

      if (data[end] == '}') { close = true; }
      else { begin = end + 1; }

      //processing line
      int count = 0;
      for (unsigned i = 0; i < line.size(); ++i) {
        if (line[i] == ':') { count++; }
      }
      if (count != 1) { throw UnitException("Invalid syntax!"); }

      std::string tag = line.substr(0, line.find(":"));
      std::string value = line.substr(line.find(":") + 1);

      if ((tag.front() != '\"') || (tag.back() != '\"')) { throw UnitException("Invalid syntax!"); }

      tag = tag.substr(1, tag.size() - 2);

      if (tag.size() <= 0) { throw UnitException("Invalid syntax!"); }

      if (value.size() <= 0) { throw UnitException("Invalid syntax!"); }

      //check tags
      if (tag == "name") {
        if ((value.front() != '\"') || (value.back() != '\"')) { throw UnitException("Invalid syntax!"); }
        value = value.substr(1, value.size() - 2);

        if (value.size() <= 0) { throw UnitException("Invalid syntax!"); }

        ret.name = value;
      }
      else if (tag == "hp") {
        ret.health = std::stoi(value);
      }
      else if (tag == "dmg") {
        ret.damage = std::stoi(value);
      }
    }

    file.close();
  }
  else {
    //throw exception
    throw UnitException("Failed to open file!");
  }
  return ret;
}

void Unit::attack(Unit& other) {
  if (health > 0) {
    //std::cout << std::endl << name << " attacks " << other.get_name() << std::endl;
    other.suffer_damage(damage);
    //std::cout << *this << std::endl << other << std::endl;
  }
}

void Unit::suffer_damage(const float& damage) {
  health -= damage;
  if (health < 0) { health = 0; }
}
