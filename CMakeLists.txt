cmake_minimum_required(VERSION 3.0)
project(C_Things_Library)

# Build C_Things_Library library
file(GLOB C_THINGS_SOURCES "src/*.c")
add_library(cthings STATIC ${C_THINGS_SOURCES})
