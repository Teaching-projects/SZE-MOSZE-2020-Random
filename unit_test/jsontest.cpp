#include "../sources/JSON.h"
#include <gtest/gtest.h>

#include <fstream>
#include <string>

TEST(JsonTest, string_parse) {
  JSON test = JSON::parseFromString("{\"key1\":\"string value\", \"key2\":.125, \"key3\":1998, \"key4\":-1.1, \"key5\":-100}");

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"string value");
  ASSERT_EQ(test.get<float>("key2"), (float)0.125);
  ASSERT_EQ(test.get<int>("key3"), (int)1998);
  ASSERT_EQ(test.get<float>("key4"), (float)-1.1);
  ASSERT_EQ(test.get<int>("key5"), (int)-100);
}

TEST(JsonTest, file_parse) {
  JSON test = JSON::parseFromFile("parse_test.json");

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"this is a string");
  ASSERT_EQ(test.get<float>("key2"), (float)0.333);
  ASSERT_EQ(test.get<int>("key3"), (int)345);
  ASSERT_EQ(test.get<float>("key4"), (float)-0.425);
  ASSERT_EQ(test.get<int>("key5"), (int)-129);
  ASSERT_EQ(test.get<std::string>("key6"), (std::string)"value");
  ASSERT_EQ(test.get<float>("key7"), (float)-0.5);
  ASSERT_EQ(test.get<float>("key8"), (float)3.14);
}

TEST(JsonTest, stream_parse) {
  std::ifstream file("parse_test.json");
  JSON test = JSON::parseFromStream(file);

  ASSERT_EQ(test.get<std::string>("key1"), (std::string)"this is a string");
  ASSERT_EQ(test.get<float>("key2"), (float)0.333);
  ASSERT_EQ(test.get<int>("key3"), (int)345);
  ASSERT_EQ(test.get<float>("key4"), (float)-0.425);
  ASSERT_EQ(test.get<int>("key5"), (int)-129);
  ASSERT_EQ(test.get<std::string>("key6"), (std::string)"value");
  ASSERT_EQ(test.get<float>("key7"), (float)-0.5);
  ASSERT_EQ(test.get<float>("key8"), (float)3.14);
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
