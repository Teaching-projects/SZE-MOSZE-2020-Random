#include "../sources/Monster.h"
#include "../sources/Hero.h"
#include "../sources/JSON.h"
#include "../sources/Map.h"
#include "../sources/Game.h"
#include "../sources/MarkedMap.h"
#include "../sources/PreparedGame.h"

#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <sstream>
#include <thread>

TEST(JsonTest, string_parse) {
  JSON test = JSON::parseFromString("{key1:\"string value\", \"key2\":.125, \"key3\":1998, \"key4\":-1.1, \"key5\":-100, \"key6\":[1,2,3,4, 5]}");

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"string value");
  ASSERT_EQ(test.get<float>("key2"), (float)0.125);
  ASSERT_EQ(test.get<int>("key3"), (int)1998);
  ASSERT_EQ(test.get<float>("key4"), (float)-1.1);
  ASSERT_EQ(test.get<int>("key5"), (int)-100);

  JSON::List list = test.get<JSON::List>("key6");
  int it = 1;
  for (const auto& l : list) {
    ASSERT_EQ(std::get<int>(l), it);
    ++it;
  }
}

TEST(JsonTest, file_parse) {
  JSON test = JSON::parseFromFile("parse_test.json");

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"this, is, a, string");
  ASSERT_EQ(test.get<float>("key2"), (float)0.333);
  ASSERT_EQ(test.get<int>("key3"), (int)345);
  ASSERT_EQ(test.get<float>("key4"), (float)-0.425);
  ASSERT_EQ(test.get<int>("key5"), (int)-129);
  ASSERT_EQ(test.get<std::string>("key6"), (std::string)"value");
  ASSERT_EQ(test.get<float>("key7"), (float)-0.5);
  ASSERT_EQ(test.get<float>("key8"), (float)3.14);

  JSON::List list = test.get<JSON::List>("key9");
  int it = 1;
  for (const auto& l : list) {
    ASSERT_EQ(std::get<int>(l), it);
    ++it;
  }
}

TEST(JsonTest, stream_parse) {
  std::ifstream file("parse_test.json");
  JSON test = JSON::parseFromStream(file);

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"this, is, a, string");
  ASSERT_EQ(test.get<float>("key2"), (float)0.333);
  ASSERT_EQ(test.get<int>("key3"), (int)345);
  ASSERT_EQ(test.get<float>("key4"), (float)-0.425);
  ASSERT_EQ(test.get<int>("key5"), (int)-129);
  ASSERT_EQ(test.get<std::string>("key6"), (std::string)"value");
  ASSERT_EQ(test.get<float>("key7"), (float)-0.5);
  ASSERT_EQ(test.get<float>("key8"), (float)3.14);

  JSON::List list = test.get<JSON::List>("key9");
  int it = 1;
  for (const auto& l : list) {
    ASSERT_EQ(std::get<int>(l), it);
    ++it;
  }
}

TEST(JsonTest, flexibility_test) {
  JSON test1 = JSON::parseFromFile("parse_test.json");
  JSON test2 = JSON::parseFromFile("parse_test2.json");

  int strings[] = {1, 6};
  int floats[] = {2, 4, 7, 8};
  int ints[] = {3, 5};

  for (int i = 0; i < 2; ++i) {
    std::string key = "key" + std::to_string(strings[i]);
    ASSERT_EQ(test1.get<std::string>(key), test2.get<std::string>(key));
  }

  for (int i = 0; i < 4; ++i) {
    std::string key = "key" + std::to_string(floats[i]);
    ASSERT_EQ(test1.get<float>(key), test2.get<float>(key));
  }

  for (int i = 0; i < 2; ++i) {
    std::string key = "key" + std::to_string(ints[i]);
    ASSERT_EQ(test1.get<int>(key), test2.get<int>(key));
  }

  int arr1[9];
  int arr2[9];

  JSON::List list = test1.get<JSON::List>("key9");
  int it = 0;
  for (const auto& l : list) {
    arr1[it] = std::get<int>(l);
    ++it;
  }

  list = test2.get<JSON::List>("key9");
  it = 0;
  for (const auto& l : list) {
    arr2[it] = std::get<int>(l);
    ++it;
  }

  for (int i = 0; i < 9; ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(JsonTest, exceptions) {
  std::ifstream file;
  JSON test;

  ASSERT_THROW(test.parseFromString(""), JSON::ParseException);
  ASSERT_THROW(test.parseFromFile(""), JSON::ParseException);
  ASSERT_THROW(test.parseFromStream(file), JSON::ParseException);

  test = JSON::parseFromFile("parse_test.json");

  ASSERT_THROW(test.get<std::string>("key2"), JSON::ParseException);
  ASSERT_THROW(test.get<float>("key1"), JSON::ParseException);
  ASSERT_THROW(test.get<int>("key1"), JSON::ParseException);

  ASSERT_THROW(JSON::parseFromString("{\"key1\":\"string value\", \"key2\":.125, \"key3\":1998"), JSON::ParseException);
  ASSERT_THROW(JSON::parseFromString("{\"key1\":\"string value\", \"key1\":.125, \"key1\":1998}"), JSON::ParseException);

}

TEST(MonsterTest, parse_test) {
  Monster m1 = Monster::parse("test_monster1.json");
  Monster m2 = Monster::parse("test_monster2.json");

  ASSERT_EQ(m1.getName(), "Monster1");
  ASSERT_EQ(m2.getName(), "Monster2");

  ASSERT_EQ(m1.getHealthPoints(), m2.getHealthPoints());
  ASSERT_EQ(m1.getDamage().physical, m2.getDamage().physical);
  ASSERT_EQ(m1.getDamage().magical, m2.getDamage().magical);
  ASSERT_EQ(m1.getAttackCooldown(), m2.getAttackCooldown());
  ASSERT_EQ(m1.getDefense(), m2.getDefense());
}

TEST(MonsterTest, attack_test) {
  Monster m1 = Monster::parse("test_monster1.json");
  Monster m2 = Monster::parse("test_monster2.json");

  ASSERT_EQ(m1.getHealthPoints(), m2.getHealthPoints());

  m1.elapseTime(m1.getAttackCooldown());

  ASSERT_EQ(m1.canHit(), true);

  m1.attack(m2);

  ASSERT_EQ(m1.getHealthPoints() - m1.getDamage().total(m2.getDefense()), m2.getHealthPoints());

  while(m2.getHealthPoints() > 0) {
    m1.attack(m2);
    m1.elapseTime(m1.getAttackCooldown());
  }
  ASSERT_EQ(m2.getHealthPoints(), 0);
  ASSERT_EQ(m2.isAlive(), false);
}

TEST(MonsterTest, exceptions) {
  ASSERT_THROW(Monster::parse("no_file_like_this"), JSON::ParseException);
}

TEST(HeroTest, parse_test) {
  Hero h1 = Hero::parse("test_hero1.json");
  Hero h2 = Hero::parse("test_hero2.json");

  ASSERT_EQ(h1.getName(), "Hero1");
  ASSERT_EQ(h2.getName(), "Hero2");

  ASSERT_EQ(h1.getHealthPoints(), 100);
  ASSERT_EQ(h2.getHealthPoints(), 50);

  ASSERT_EQ(h1.getDamage().physical, 50);
  ASSERT_EQ(h1.getDamage().magical, 25);
  ASSERT_EQ(h2.getDamage().physical, 10);
  ASSERT_EQ(h2.getDamage().magical, 0);

  ASSERT_EQ(h1.getDefense(), 5);
  ASSERT_EQ(h2.getDefense(), 25);

  ASSERT_EQ(h1.getLightRadius(), 1);
  ASSERT_EQ(h2.getLightRadius(), 2);

  ASSERT_EQ(h1.getAttackCooldown(), (float)1.3);
  ASSERT_EQ(h2.getAttackCooldown(), (float)1.5);

  ASSERT_EQ(h1.getMaxHealthPoints(), 100);
  ASSERT_EQ(h2.getMaxHealthPoints(), 50);

  ASSERT_EQ(h1.getLevel(), 1);
  ASSERT_EQ(h1.getLevel(), h2.getLevel());
}

TEST(HeroTest, attack_test) {
  Hero h1 = Hero::parse("test_hero1.json");
  Hero h2 = Hero::parse("test_hero2.json");

  ASSERT_EQ(h1.getLevel(), h2.getLevel());

  h1.elapseTime(h1.getAttackCooldown());

  int dam = h1.getDamage().total(h2.getDefense());
  ASSERT_EQ(h1.canHit(), true);

  h1.attack(h2);

  ASSERT_EQ(h2.getHealthPoints() + dam, h2.getMaxHealthPoints());
  ASSERT_GT(h1.getMaxHealthPoints(), h2.getMaxHealthPoints());
  ASSERT_GT(h1.getLevel(), h2.getLevel());
  ASSERT_EQ(h1.getLevel(), 2);
  ASSERT_EQ(h2.getLevel(), 1);
}

TEST(HeroTest, levelup_test) {
  Hero h1 = Hero::parse("test_hero1.json");
  Hero h1c = Hero::parse("test_hero1.json");

  Hero h2 = Hero::parse("test_hero2.json");

  ASSERT_EQ(h1.getName(), "Hero1");
  ASSERT_EQ(h2.getName(), "Hero2");

  ASSERT_EQ(h1.getHealthPoints(), h1c.getHealthPoints());
  ASSERT_EQ(h1.getDamage().physical, h1c.getDamage().physical);
  ASSERT_EQ(h1.getDamage().magical, h1c.getDamage().magical);
  ASSERT_EQ(h1.getAttackCooldown(), h1c.getAttackCooldown());
  ASSERT_EQ(h1.getMaxHealthPoints(), h1c.getMaxHealthPoints());
  ASSERT_EQ(h1.getLevel(), h1c.getLevel());

  ASSERT_EQ(h1.getLevel(), h2.getLevel());

  h1.elapseTime(h1.getAttackCooldown());
  h2.elapseTime(h2.getAttackCooldown());

  ASSERT_EQ(h1.canHit(), true);

  h2.attack(h1);
  h1.attack(h2);

  ASSERT_EQ(h1.getHealthPoints(), h1.getMaxHealthPoints());
  ASSERT_GT(h1.getLevel(), h2.getLevel());
  ASSERT_EQ(h1.getLevel(), 2);
  ASSERT_EQ(h2.getLevel(), 1);

  ASSERT_EQ(h1.getHealthPoints(), h1c.getHealthPoints() + 50);
  ASSERT_EQ(h1.getDamage().physical, h1c.getDamage().physical + 50);
  ASSERT_EQ(h1.getDamage().magical, h1c.getDamage().magical + 5);
  ASSERT_EQ(h1.getAttackCooldown(), h1c.getAttackCooldown() * 0.5);
  ASSERT_EQ(h1.getMaxHealthPoints(), h1c.getMaxHealthPoints() + 50);
  ASSERT_EQ(h1.getLevel(), h1c.getLevel() + 1);
  ASSERT_EQ(h1.getDefense(), h1c.getDefense() + 1);
  ASSERT_EQ(h1.getLightRadius(), h1c.getLightRadius() + 2);
}

TEST(HeroTest, exceptions) {
  ASSERT_THROW(Monster::parse("does_not_exist"), JSON::ParseException);
}

TEST(MapTest, function_test) {
  Map map("test_map");
  ASSERT_EQ(map.getWidth(), 3);
  ASSERT_EQ(map.getHeight(), 4);
  ASSERT_EQ(map.get(1, 1), Map::Free);
  ASSERT_EQ(map.get(0, 2), Map::Wall);
}

TEST(MapTest, exceptions) {
  Map map;
  ASSERT_THROW(map.get(0, 2), Map::WrongIndexException);
  ASSERT_THROW(Map("nonexistent"), Map::FileNotFoundException);
  ASSERT_THROW(Map("test_hero1.json"), Map::InvalidFileException);
}

TEST(GameTest, functions) {
  Game game("test_map");
  game.setMap(Map("test_map"));

  Hero hero = Hero::parse("test_hero2.json");
  Monster monster = Monster::parse("test_monster3.json");
  game.putHero(hero, 0, 1);
  game.putMonster(monster, 1, 1);
  std::stringstream ss1;
  ss1.str("east");
  game.run(ss1);
  ASSERT_EQ(game.hasHero(), false);

  hero = Hero::parse("test_hero1.json");
  game.putHero(hero, 0, 1);
  std::stringstream ss2;
  ss2.str("east");
  game.run(ss2);
  ASSERT_EQ(game.hasHero(), true);
}

TEST(GameTest, exceptions) {
  //OccupiedException
  //AlreadyHasHeroException
  //AlreadyHasUnitsException
  //NotInitializedException
  //GameAlreadyStartedException
  class TestGame : public Game {
  public:
    void enableRunning() { running = true; }
  };

  Hero hero = Hero::parse("test_hero1.json");
  Monster monster = Monster::parse("test_monster3.json");
  std::stringstream ss;
  TestGame game;

  ASSERT_THROW(game.run(ss), Game::NotInitializedException);

  game.setMap(Map("test_map"));

  ASSERT_THROW(game.putHero(hero, -1, 0), Map::WrongIndexException);
  ASSERT_THROW(game.putHero(hero, 100, 0), Map::WrongIndexException);
  ASSERT_THROW(game.putHero(hero, 0, -1), Map::WrongIndexException);
  ASSERT_THROW(game.putHero(hero, 0, 100), Map::WrongIndexException);
  ASSERT_THROW(game.putHero(hero, -1, -1), Map::WrongIndexException);
  ASSERT_THROW(game.putHero(hero, 100, 100), Map::WrongIndexException);

  ASSERT_THROW(game.putMonster(monster, -1, 0), Map::WrongIndexException);
  ASSERT_THROW(game.putMonster(monster, 100, 0), Map::WrongIndexException);
  ASSERT_THROW(game.putMonster(monster, 0, -1), Map::WrongIndexException);
  ASSERT_THROW(game.putMonster(monster, 0, 100), Map::WrongIndexException);
  ASSERT_THROW(game.putMonster(monster, -1, -1), Map::WrongIndexException);
  ASSERT_THROW(game.putMonster(monster, 100, 100), Map::WrongIndexException);

  ASSERT_THROW(game.run(ss), Game::NotInitializedException);

  ASSERT_THROW(game.putHero(hero, 0, 0), Game::OccupiedException);
  game.putHero(hero, 0, 1);
  ASSERT_THROW(game.putHero(hero, 0, 2), Game::AlreadyHasHeroException);

  ASSERT_THROW(game.run(ss), Game::NotInitializedException);

  ASSERT_THROW(game.putMonster(monster, 0, 0), Game::OccupiedException);
  game.putMonster(monster, 1, 1);

  ASSERT_THROW(game.setMap(Map("test_map")), Game::AlreadyHasUnitsException);

  game.enableRunning();

  ASSERT_THROW(game.setMap(Map("test_map")), Game::GameAlreadyStartedException);
  ASSERT_THROW(game.putHero(hero, 0, 1), Game::GameAlreadyStartedException);
  ASSERT_THROW(game.putMonster(monster, 0, 2), Game::GameAlreadyStartedException);
  ASSERT_THROW(game.run(ss), Game::GameAlreadyStartedException);
}

TEST(MarkedMapTest, functions) {
  MarkedMap map("test_map2");

  ASSERT_EQ(map.getHeroPosition().x, 1);
  ASSERT_EQ(map.getHeroPosition().y, 1);

  ASSERT_EQ(map.getMonsterPositions('1').size(), 2);

  ASSERT_EQ(map.getMonsterIDs().front(), '1');
  ASSERT_EQ(map.getMonsterIDs().back(), '2');

  ASSERT_EQ(map.getMonsterPositions('2').front().x, 0);
  ASSERT_EQ(map.getMonsterPositions('2').front().y, 2);
}

TEST(MarkedMapTest, exceptions) {
  MarkedMap map("test_map2");

  ASSERT_THROW(map.getMonsterPositions('9'), Map::WrongIndexException);

  ASSERT_THROW(MarkedMap("nonexistent"), Map::FileNotFoundException);
  ASSERT_THROW(MarkedMap("test_map"), Map::InvalidFileException);
}

TEST(PreparedGameTest, exceptions) {
  ASSERT_THROW(PreparedGame("no_game_no_life"), JSON::ParseException);
  ASSERT_THROW(PreparedGame("test_monster1.json"), JSON::ParseException);
  ASSERT_THROW(PreparedGame("test_bad_gameconfig.json"), JSON::ParseException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
