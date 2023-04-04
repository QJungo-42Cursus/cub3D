#include "./gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

extern "C" {
#include "../src/cube3D.h"
}

static void init_map_(t_map *map) {
  map->textures[NORTH].pixels = NULL;
  map->textures[SOUTH].pixels = NULL;
  map->textures[WEST].pixels = NULL;
  map->textures[EAST].pixels = NULL;
  map->tiles = NULL;
  map->size.x = 0;
  map->size.y = 0;
  map->ceiling_color = 0xFF000000;
  map->floor_color = 0xFF000000;
}

static int init_program_(t_program *program) {
  program->mlx = NULL;
  program->win = NULL;
  init_map_(program->map);
  return (EXIT_SUCCESS);
}

static void parsing_integration_test(std::string filename, std::string expected,
                                     bool free_prog = false) {
  testing::internal::CaptureStdout();

  t_program program;
  t_map map;
  program.map = &map;
  if (init_program_(&program) == EXIT_FAILURE) {
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output << "  errno: " << errno << std::endl;
    perror("mlx_init error");
	FAIL() << "mlx_init error";
  }

  {
    free_program(&program);
	std::string output = testing::internal::GetCapturedStdout();
    return;
  }

  parse((char *)filename.c_str(), &program);
  if (free_prog) {
    free_program(&program);
  }
  std::string output = testing::internal::GetCapturedStdout();
  if (expected != "-") {
    EXPECT_EQ(output, expected);
  } else {
  }
}

static void parsing_integration_test(std::string filename,
                                     bool free_prog = false) {
  parsing_integration_test(filename, "-", free_prog);
}

static void parsing_integration_test(std::vector<std::string> content,
                                     std::string expected,
                                     bool free_prog = false) {
  // write content to a file and call parsing_integration_test
  std::string filename = "tmp.cub";
  std::ofstream file(filename);
  for (std::string line : content) {
    file << line << std::endl;
  }
  file.close();
  parsing_integration_test(filename, expected, free_prog);
  remove(filename.c_str());
}

static std::vector<std::string> working_infos = {"NO ../textures/wood.xpm",
                                                 "SO ../textures/wood.xpm",
                                                 "WE ../textures/wood.xpm",
                                                 "EA ../textures/wood.xpm\n",
                                                 "F 0,0,0",
                                                 "C 0,0,0\n"};

/*************** TESTS ***************/

TEST(ParsingIntegrationTest, UnexistingFile) {
  parsing_integration_test("../maps/unexisting.cub",
                           "Error\ncould not open file\n");
}

TEST(ParsingIntegrationTest, EmptyFile) {
  parsing_integration_test("../maps/failing_maps/empty.cub",
                           "Error\nfile is empty\n");
}

TEST(ParsingIntegrationTest, TextureAfterMap) {
  parsing_integration_test("../maps/failing_maps/texture_after_map.cub",
                           "Error\nmap is not at the end of the file\n");
}

TEST(ParsingIntegrationTest, DuplicateTexture) {
  parsing_integration_test(
      "../maps/failing_maps/duplicate_texture.cub",
      "Error\nmultiple definition for same texture or color\n");
}

TEST(ParsingIntegrationTest, WrongTexturePath) {
  parsing_integration_test("../maps/failing_maps/wrong_texture_path.cub",
                           "Error\ntexture path or color not found\n");
}

TEST(ParsingIntegrationTest, MissingTexture) {
  parsing_integration_test("../maps/failing_maps/missing_texture.cub",
                           "Error\ntexture path or color not found\n");
}

TEST(ParsingIntegrationTest, WrongColor) {
  parsing_integration_test("../maps/failing_maps/wrong_color.cub",
                           "Error\ncolor format error\n");
}

TEST(ParsingIntegrationTest, UnclosedMap) {
  std::vector<std::string> content = working_infos;
  content.push_back("111N111111111");
  parsing_integration_test(content, "Error\nMap is not closed\n", true);
}

TEST(ParsingIntegrationTest, UnclosedMap2) {
  std::vector<std::string> content = working_infos;
  content.push_back("1111111111111");
  content.push_back("1N00000000000");
  content.push_back("1000000000001");
  content.push_back("1111111111111");
  parsing_integration_test(content, "Error\nMap is not closed\n", true);
}

TEST(ParsingIntegrationTest, UnclosedMap3) {
  std::vector<std::string> content = working_infos;
  content.push_back("          1111111111111          ");
  content.push_back("1000000000001          ");
  content.push_back("100000000E001          ");
  content.push_back("1111111111111          ");
  parsing_integration_test(content, "Error\nMap is not closed\n", true);
}

TEST(ParsingIntegrationTest, TrickyMap) {
  std::vector<std::string> content = working_infos;
  content.push_back("");
  content.push_back("                    111111111111           ");
  content.push_back("          1111111111100000000001   ");
  content.push_back("          100000000E001111111111 ");
  content.push_back("          1111111111111          ");
  content.push_back("");
  content.push_back("");
  content.push_back("");
  content.push_back("");
  content.push_back("");
  content.push_back("");
  parsing_integration_test(content, "", true);
}

TEST(ParsingIntegrationTest, EmptyLine) {
  std::vector<std::string> content = working_infos;
  content.push_back("                                               ");
  content.push_back("                    111111111111           ");
  content.push_back("          1111111111100000000001   ");
  content.push_back("          100000000E001111111111 ");
  content.push_back("          1111111111111          ");
  content.push_back("                                               ");
  parsing_integration_test(content, "Error\nmap has an empty line\n", true);
}

TEST(ParsingIntegrationTest, Basic) {
  parsing_integration_test("../maps/basic.cub", "");
}

/*
TEST(ParsingIntegrationTest, TestAllInvalidMap) {
  std::string path = "./../maps/invalid_maps/";
#ifdef __APPLE__
  for (const auto &entry : std::__fs::filesystem::directory_iterator(path)) {
#else
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
#endif
    parsing_integration_test(entry.path(), true);
  }
}
*/
