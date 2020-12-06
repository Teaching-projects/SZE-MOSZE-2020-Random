#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "PreparedGame.h"

const std::map<int,std::string> error_messages = {
  { 1 , "Bad number of arguments. Only a single configuration file should be provided." },
  { 2 , "The provided configuration file is not accessible." },
  { 3 , "The provided scenario file is invalid." },
  { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
  std::cerr << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
            << std::endl;
  exit(exitcode);
}

int main(int argc, char** argv){
  if (argc != 2) bad_exit(1);
  if (!std::filesystem::exists(argv[1])) bad_exit(2);

  try {
    PreparedGame game(argv[1]);
    game.run();
  }
  catch (const JSON::ParseException& e) {
    std::cerr << e.what() << std::endl;
    bad_exit(4);
  }

  return 0;
}
