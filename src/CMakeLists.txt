# ---- library definition ----

target_sources(template_lib
  PUBLIC
  FILE_SET template_lib_file_set
  TYPE HEADERS FILES
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib.hpp>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/template/lib.hpp>
  PRIVATE
  lib.cpp
)
target_link_libraries(template_lib
  PRIVATE
  template_compile_options
)

# ---- testing ----

if(BUILD_TESTING)
  include(Catch)

  enable_testing()

  find_package(Catch2 REQUIRED)
  add_executable(template_lib_test)
  target_sources(template_lib_test
    PRIVATE
    lib.test.cpp
  )
  target_link_libraries(template_lib_test
    PRIVATE
    template_lib
    template_compile_options
    Catch2::Catch2WithMain
  )
  target_precompile_headers(template_lib_test
    PRIVATE
    <catch2/catch_test_macros.hpp>
  )
  catch_discover_tests(template_lib_test
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
