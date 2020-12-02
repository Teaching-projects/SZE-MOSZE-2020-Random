cmake_minimum_required(VERSION 2.6)
project(basic_test)
set (CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test
# and the GTest and pthread library
add_executable(runTests unit_test.cpp ../sources/Game.cpp ../sources/Map.cpp ../sources/Monster.cpp ../sources/Hero.cpp ../sources/JSON.cpp ../sources/JSONList.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
