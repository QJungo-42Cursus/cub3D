#include "gtest/gtest.h"

extern "C" {
#include "../cube3D.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}