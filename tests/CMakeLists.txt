enable_testing()

file(GLOB TestSources "*.c")
foreach(TestSource ${TestSources})
  # extract filename without extension and use it as test executable's name
  get_filename_component(TestFileName ${TestSource} NAME_WE)
  add_executable(${TestFileName} ${TestSource})

  # link against cthings framework
  target_link_libraries(${TestFileName} cthings)

  add_test(NAME ${TestFileName} COMMAND ${TestFileName})
endforeach()
