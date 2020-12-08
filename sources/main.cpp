#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Map.h"
#include "Game.h"
#include "PreparedGame.h"

#include "HeroTextRenderer.h"
#include "ObserverTextRenderer.h"
#include "HeroSVGRenderer.h"

const std::map<int,std::string> error_messages = {
  { 1 , "Bad number of arguments. Only a single configuration file should be provided." },
  { 2 , "The provided configuration file is not accessible." },
  { 3 , "JSON parsing error." },
  { 4 , "The provided map file is not accessible." },
  { 5 , "The provided map file is invalid." },
  { 6 , "Invalid access on map." },
  { 7 , "Multiple hero placement is forbidden." },
  { 8 , "Map change while units are initialized is forbidden." },
  { 9 , "Tried to change the game after it has been started." },
  { 10 , "Game not initialized properly." },
  { 11 , "The given position is not accessible." }
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
    std::ofstream renderFile("../text_render.txt");

    PreparedGame game(argv[1]);
    game.registerRenderer(new HeroTextRenderer());
    game.registerRenderer(new HeroSVGRenderer("../svg_image.svg"));
    game.registerRenderer(new ObserverTextRenderer(renderFile));
    game.run();

    renderFile.close();
  }
  catch (const JSON::ParseException& e) {
    std::cerr << e.what() << std::endl;
    bad_exit(3);
  }
  catch ( const Map::FileNotFoundException& e) {
    bad_exit(4);
  }
  catch ( const Map::InvalidFileException& e) {
    bad_exit(5);
  }
  catch ( const Map::WrongIndexException& e) {
    bad_exit(6);
  }
  catch ( const Game::AlreadyHasHeroException& e) {
    bad_exit(7);
  }
  catch ( const Game::AlreadyHasUnitsException& e) {
    bad_exit(8);
  }
  catch ( const Game::GameAlreadyStartedException& e) {
    bad_exit(9);
  }
  catch ( const Game::NotInitializedException& e) {
    bad_exit(10);
  }
  catch ( const Game::OccupiedException& e) {
    bad_exit(11);
  }
  return 0;
}
