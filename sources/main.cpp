#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Map.h"
#include "Game.h"




const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
    std::cerr
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]);
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            JSON::List monster_file_list = scenario.get<JSON::List>("monsters");
            for(auto monster_file : monster_file_list) {
              monster_files.push_back(std::get<std::string>(monster_file));}
        }
    } catch (const JSON::ParseException& e) {std::cerr<<e.what()<<std::endl;bad_exit(4);}

    try {
      Hero hero{Hero::parse(hero_file)};
      Game game("../maps/map1");

      game.putHero(hero, 1, 1);

      game.putMonster(Monster::parse(monster_files.back()), 2, 5);
      for (const auto& m : monster_files) {
        game.putMonster(Monster::parse(m), 4, 5);
      }

      game.run();

    } catch (const JSON::ParseException& e) {bad_exit(4);}

    return 0;
}
