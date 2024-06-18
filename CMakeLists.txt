cmake_minimum_required(VERSION 3.0)
project(C_Things_Library)

# Build C_Things_Library library
file(GLOB C_Things_Sources "src/*.c")
add_library(cthings STATIC ${C_Things_Sources})

enable_testing()

file(GLOB TestSources "tests/*.c")
foreach(TestSource ${TestSources})
  get_filename_component(TestFileName ${TestSource} NAME_WE)
  add_executable(${TestFileName} ${TestSource})
  target_link_libraries(${TestFileName} cthings)
  add_test(NAME ${TestFileName} COMMAND ${TestFileName})
endforeach()
