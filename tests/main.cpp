#include "gtest/gtest.h"

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

/*
#./$(NAME) tests/failing_maps/invalide_name.cu || true
#@echo
#./$(NAME) tests/failing_maps/unexisting.cub || true
#@echo
#./$(NAME) tests/failing_maps/empty.cub || true
#@echo
#./$(NAME) tests/failing_maps/texture_after_map.cub || true
#@echo
#./$(NAME) tests/failing_maps/duplicate_texture.cub || true
#@echo
#./$(NAME) tests/failing_maps/wrong_texture_path.cub || true
#@echo
#./$(NAME) tests/failing_maps/missing_texture.cub || true
#@echo
#./$(NAME) tests/failing_maps/wrong_color.cub || true
#
#@echo
#./$(NAME) tests/basic.cub || true
*/


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
