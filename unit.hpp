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
protected:
  std::string name = "";
  float health = 0;
  float damage = 0;

public:
  Unit() : name(""), health(0), damage(0) {}
  Unit(const std::string& n, const float& h, const float& d) : name(n), health(h), damage(d) {}
  //~Unit() {}

  //operator overload
  friend std::ostream& operator<<(std::ostream& os, const Unit& unit);

  //functions
  static Unit parse_unit(const std::string& filename);
  virtual void attack(Unit& other);
  void suffer_damage(const float& damage);

  //getters
  std::string get_name() const { return name; }
  float get_health() const { return health; }
  float get_damage() const { return damage; }
};

#endif
