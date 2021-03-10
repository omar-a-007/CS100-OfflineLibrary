#include <gtest/gtest.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>

#include "../headers/library.h"

#include "iComponent_test.h"
#include "user_test.h"
#include "transaction_test.h"
#include "DBwrapper_test.h"
#include "library_test.h"

const std::string DBwrapper::DBfile{"test.db3"};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();

  // std::cout << "Ready to quit?\n";
  // std::string answer;
  // std::cin >> answer;                // Delay added so test.db3 can be inspected if needed.

  remove("test.db3");

  return result;
}

