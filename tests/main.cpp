#include "./gtest/gtest.h"

extern "C" {
#include "../src/cube3D.h"
}

int main(int argc, char **argv) {
  void *mlx = mlx_init();
  mlx = NULL;
  //::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
}
