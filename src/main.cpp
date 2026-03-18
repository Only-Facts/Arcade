/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade
*/

#include <iostream>
#include "Core.hpp"

static unsigned int handle_args(int argc, const char *argv[]) {
  if (argc != 2 || !argv || !argv[1]) {
    std::cerr <<
      "Usage:\n\tarcade [options] <file>\nOptions:\n\t-h, --help Show this help" <<
      std::endl;
    return ERROR;
  }

  std::string flag(argv[1]);
  if (flag == "--help" || flag == "-h") {
    std::cout <<
      "Usage:\n\tarcade [options] <file>\nOptions:\n\t-h, --help Show this help" <<
      std::endl;
    return HELP;
  }
  return SUCCESS;
}

int main(int argc, const char *argv[]) {
  switch (handle_args(argc, argv)) {
    case HELP:
      return SUCCESS;
    case ERROR:
      return ERROR;
    default:
      return SUCCESS;
  }
}
