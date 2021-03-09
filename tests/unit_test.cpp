#include <gtest/gtest.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>

#include "../headers/library.h"

#include "iComponent_test.h"

const std::string DBwrapper::DBfile{"test.db3"};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  remove("test.db3");
}

