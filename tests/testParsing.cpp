#include "gtest/gtest.h"

extern "C" {
#include "../cube3D.h"
}

static void init_map(t_map *map) {
  map->no_path = NULL;
  map->so_path = NULL;
  map->we_path = NULL;
  map->ea_path = NULL;
  map->tiles = NULL;
}

static void parsing_integration_test(std::string filename,
                                     std::string expected) {
  int pid = fork();
  if (pid == 0) {
    t_map map;
    init_map(&map);
    testing::internal::CaptureStdout();
    parse((char *)filename.c_str(), &map);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, expected);
    exit(0);
  } else {
    waitpid(pid, NULL, 0);
  }
}

TEST(ParsingIntegrationTest, UnexistingFile) {
  parsing_integration_test("test_files/unexisting.cub",
                           "Error\ncould not open file\n");
}

TEST(ParsingIntegrationTest, EmptyFile) {
  parsing_integration_test("test_files/failing_maps/empty.cub",
                           "Error\nfile is empty\n");
}

TEST(ParsingIntegrationTest, TextureAfterMap) {
  parsing_integration_test("test_files/failing_maps/texture_after_map.cub",
                           "Error\nmap is not at the end of the file\n");
}

TEST(ParsingIntegrationTest, DuplicateTexture) {
  parsing_integration_test(
      "test_files/failing_maps/duplicate_texture.cub",
      "Error\nmultiple definition for same texture or color\n");
}

TEST(ParsingIntegrationTest, WrongTexturePath) {
  parsing_integration_test("test_files/failing_maps/wrong_texture_path.cub",
                           "Error\ntexture path is not valid\n");
}

TEST(ParsingIntegrationTest, MissingTexture) {
  parsing_integration_test("test_files/failing_maps/missing_texture.cub",
                           "Error\npath not found\n");
}

TEST(ParsingIntegrationTest, WrongColor) {
  parsing_integration_test("test_files/failing_maps/wrong_color.cub",
                           "Error\ncolor format error\n");
}

TEST(ParsingIntegrationTest, Basic) {
  parsing_integration_test("test_files/basic.cub", "");
}
