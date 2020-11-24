#include "../sources/Monster.h"
#include "../sources/Hero.h"
#include "../sources/JSON.h"
#include <gtest/gtest.h>

#include <fstream>
#include <string>

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
    std::cerr << it << std::endl;
    ++it;
  }
  std::cerr << "done" << std::endl;

  list = test2.get<JSON::List>("key9");
  it = 0;
  for (const auto& l : list) {
    arr2[it] = std::get<int>(l);
    std::cerr << it << std::endl;
    ++it;
  }
  std::cerr << "done" << std::endl;

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
  ASSERT_EQ(m1.getDamage(), m2.getDamage());
  ASSERT_EQ(m1.getAttackCooldown(), m2.getAttackCooldown());
}

TEST(MonsterTest, attack_test) {
  Monster m1 = Monster::parse("test_monster1.json");
  Monster m2 = Monster::parse("test_monster2.json");

  ASSERT_EQ(m1.getHealthPoints(), m2.getHealthPoints());

  m1.elapseTime(m1.getAttackCooldown());

  ASSERT_EQ(m1.canHit(), true);

  m1.attack(m2);

  ASSERT_EQ(m1.getHealthPoints() - m1.getDamage(), m2.getHealthPoints());

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

  ASSERT_EQ(h1.getDamage(), 50);
  ASSERT_EQ(h2.getDamage(), 10);

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

  int dam = h1.getDamage();
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
  ASSERT_EQ(h1.getDamage(), h1c.getDamage());
  ASSERT_EQ(h1.getAttackCooldown(), h1c.getAttackCooldown());
  ASSERT_EQ(h1.getMaxHealthPoints(), h1c.getMaxHealthPoints());
  ASSERT_EQ(h1.getLevel(), h1c.getLevel());

  ASSERT_EQ(h1.getLevel(), h2.getLevel());

  h1.elapseTime(h1.getAttackCooldown());
  h2.elapseTime(h2.getAttackCooldown());

  int dam = h1.getDamage();
  ASSERT_EQ(h1.canHit(), true);

  h2.attack(h1);
  h1.attack(h2);

  ASSERT_EQ(h1.getHealthPoints(), h1.getMaxHealthPoints());
  ASSERT_GT(h1.getLevel(), h2.getLevel());
  ASSERT_EQ(h1.getLevel(), 2);
  ASSERT_EQ(h2.getLevel(), 1);

  ASSERT_EQ(h1.getHealthPoints(), h1c.getHealthPoints() + 50);
  ASSERT_EQ(h1.getDamage(), h1c.getDamage() + 50);
  ASSERT_EQ(h1.getAttackCooldown(), h1c.getAttackCooldown() * 0.5);
  ASSERT_EQ(h1.getMaxHealthPoints(), h1c.getMaxHealthPoints() + 50);
  ASSERT_EQ(h1.getLevel(), h1c.getLevel() + 1);
}

TEST(HeroTest, exceptions) {
  ASSERT_THROW(Monster::parse("does_not_exist"), JSON::ParseException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
