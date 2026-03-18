cmake_minimum_required(VERSION 3.16)

project(Arcade LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror -g)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(arcade ${SOURCES})
