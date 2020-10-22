#include "../json.hpp"
#include <gtest/gtest.h>

#include <fstream>

TEST(JsonTest, string_parse) {
  Json test;
  test.parse_string("{\"key1\":\"string value\", \"key2\":.125, \"key3\":1998, \"key4\":-1.1, \"key5\":-100}");

  ASSERT_EQ(test.get_string("key1"), (std::string)"string value");
  ASSERT_EQ(test.get_float("key2"), (float)0.125);
  ASSERT_EQ(test.get_int("key3"), (int)1998);
  ASSERT_EQ(test.get_float("key4"), (float)-1.1);
  ASSERT_EQ(test.get_int("key5"), (int)-100);
}

TEST(JsonTest, file_parse) {
  Json test;
  test.parse_file("parse_test.json");

  ASSERT_EQ(test.get_string("key1"), (std::string)"this is a string");
  ASSERT_EQ(test.get_float("key2"), (float)0.333);
  ASSERT_EQ(test.get_int("key3"), (int)345);
  ASSERT_EQ(test.get_float("key4"), (float)-0.425);
  ASSERT_EQ(test.get_int("key5"), (int)-129);
  ASSERT_EQ(test.get_string("key6"), (std::string)"value");
  ASSERT_EQ(test.get_float("key7"), (float)-0.5);
  ASSERT_EQ(test.get_float("key8"), (float)3.14);
}

TEST(JsonTest, stream_parse) {
  std::ifstream file("parse_test.json");
  Json test;
  test.parse_stream(file);

  ASSERT_EQ(test.get_string("key1"), (std::string)"this is a string");
  ASSERT_EQ(test.get_float("key2"), (float)0.333);
  ASSERT_EQ(test.get_int("key3"), (int)345);
  ASSERT_EQ(test.get_float("key4"), (float)-0.425);
  ASSERT_EQ(test.get_int("key5"), (int)-129);
  ASSERT_EQ(test.get_string("key6"), (std::string)"value");
  ASSERT_EQ(test.get_float("key7"), (float)-0.5);
  ASSERT_EQ(test.get_float("key8"), (float)3.14);
}

TEST(JsonTest, exceptions) {
  std::ifstream file;
  Json test;

  ASSERT_THROW(test.parse_string(""), JsonException);
  ASSERT_THROW(test.parse_file(""), JsonException);
  ASSERT_THROW(test.parse_stream(file), JsonException);

  test.parse_file("parse_test.json");

  ASSERT_THROW(test.get_string("key2"), JsonException);
  ASSERT_THROW(test.get_float("key1"), JsonException);
  ASSERT_THROW(test.get_int("key1"), JsonException);

  ASSERT_THROW(test.parse_string("{\"key1\":\"string value\", \"key2\":.125, \"key3\":1998"), JsonException);
  ASSERT_THROW(test.parse_string("{\"key1\":\"string value\", \"key1\":.125, \"key1\":1998}"), JsonException);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
