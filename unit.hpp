#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>

class UnitException : public std::exception {
  std::string s;
public:
  UnitException(const std::string& ss) : s(ss) {}
  ~UnitException() throw() {}
  const char* what() const throw() { return s.c_str(); }
};

class Unit {
  std::string name = "";
  float health = 0;
  float damage = 0;
  float max_cd = 0;
  float cd = 0;

  void suffer_damage(const float& damage);

public:
  Unit() : name(""), health(0), damage(0), max_cd(0), cd(0) {}
  Unit(const std::string& n, const float& h, const float& d, const float& cd) : name(n), health(h), damage(d), max_cd(cd), cd(0) {}
  //~Unit() {}

  //operator overload
  friend std::ostream& operator<<(std::ostream& os, const Unit& unit);

  //functions
  static Unit parse_unit(const std::string& filename);
  void attack(Unit& other);
  void elapse_time(const float& t);

  //getters
  std::string get_name() const { return name; }
  float get_health() const { return health; }
  float get_damage() const { return damage; }
};

#endif
