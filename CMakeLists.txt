cmake_minimum_required(VERSION 3.29.5)
project(
  C_Things_Framework
  VERSION 0.1.0
  DESCRIPTION "A C Framework"
  LANGUAGES C)

# Build C_Things_Framework as a static library
file(GLOB C_Things_Sources "src/*.c")
add_library(cthings STATIC ${C_Things_Sources})

add_subdirectory(tests)
