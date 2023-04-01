#include "gtest/gtest.h"

extern "C" {
#include "../cube3D.h"
int main_(int argc, char **argv);
}

void test_main_(const char *file_name, const char *expected_output) {
  char *argv[] = {(char *)"cube3D", (char *)file_name};
  testing::internal::CaptureStdout();
  main_(2, argv);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(expected_output, output.c_str());
}

TEST(MainTest, InvalidExtension) {
  test_main_("test_files/failing_maps/invalid_name.cu",
             "Error\nusage: ./cub3D [map_file].cub\n");
}

TEST(MainTest, basic) { test_main_("test_files/basic.cub", ""); }
