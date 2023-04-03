#include "./gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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
    if (expected != "-") {
      EXPECT_EQ(output, expected);
    } else {
      // std::cout << output;
    }
    exit(0);
  } else {
    waitpid(pid, NULL, 0);
  }
}

static void parsing_integration_test(std::string filename) {
  parsing_integration_test(filename, "-");
}

static void parsing_integration_test(std::vector<std::string> content,
                                     std::string expected) {
  // write content to a file and call parsing_integration_test
  std::string filename = "test_files/tmp.cub";
  std::ofstream file(filename);
  for (std::string line : content) {
    file << line << std::endl;
  }
  file.close();
  parsing_integration_test(filename, expected);
  remove(filename.c_str());
}

static std::vector<std::string> working_infos = {"NO ./textures/stone.xpm",
                                                 "SO ./textures/stone.xpm",
                                                 "WE ./textures/stone.xpm",
                                                 "EA ./textures/stone.xpm",
                                                 "F 0,0,0",
                                                 "C 0,0,0"};

/*************** TESTS ***************/

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

TEST(ParsingIntegrationTest, UnclosedMap) {
  std::vector<std::string> content = working_infos;
  content.push_back("111N111111111");
  parsing_integration_test(content, "Error\nMap is not closed\n");
}

TEST(ParsingIntegrationTest, UnclosedMap2) {
  std::vector<std::string> content = working_infos;
  content.push_back("1111111111111");
  content.push_back("1N00000000000");
  content.push_back("1000000000001");
  content.push_back("1111111111111");
  parsing_integration_test(content, "Error\nMap is not closed\n");
}

TEST(ParsingIntegrationTest, UnclosedMap3) {
  std::vector<std::string> content = working_infos;
  content.push_back("          1111111111111          ");
  content.push_back("1000000000001          ");
  content.push_back("100000000E001          ");
  content.push_back("1111111111111          ");
  parsing_integration_test(content, "Error\nMap is not closed\n");
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
  parsing_integration_test(content, "");
}

TEST(ParsingIntegrationTest, EmptyLine) {
  std::vector<std::string> content = working_infos;
  content.push_back("                                               ");
  content.push_back("                    111111111111           ");
  content.push_back("          1111111111100000000001   ");
  content.push_back("          100000000E001111111111 ");
  content.push_back("          1111111111111          ");
  content.push_back("                                               ");
  parsing_integration_test(content, "Error\nmap has an empty line\n");
}

TEST(ParsingIntegrationTest, TestAllInvalidMap) {
  std::string path = "./test_files/invalid_maps/";
#ifdef __APPLE__
  for (const auto &entry : std::__fs::filesystem::directory_iterator(path)) {
#else
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
#endif
    parsing_integration_test(entry.path());
  }
}
