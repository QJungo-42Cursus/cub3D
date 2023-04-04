#include "./gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

extern "C" {
#include "../src/cube3D.h"
}

static void parsing_integration_test(std::string filename, std::string expected,
                                     bool free_prog = false) {
  testing::internal::CaptureStdout();

  std::cerr << "salut maman 03" << std::endl;

  t_program program;
  t_map map;
  program.map = &map;
  init_program(&program);
  std::cerr << "salut maman 04" << std::endl;
  parse((char *)filename.c_str(), &program);
  std::cerr << "salut maman 05" << std::endl;
  if (free_prog) {
    free_program(&program);
  }

  std::cerr << "salut maman 06" << std::endl;
  std::string output = testing::internal::GetCapturedStdout();

  std::cout << output << "salut maman" << std::endl;
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
  std::cout << "salut maman 01" << std::endl;
  parsing_integration_test("../maps/unexisting.cub",
                           "Error\ncould not open file\n", true);
  std::cout << "salut maman 02" << std::endl;
}

TEST(ParsingIntegrationTest, EmptyFile) {
  std::cout << "salut maman" << std::endl;
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
