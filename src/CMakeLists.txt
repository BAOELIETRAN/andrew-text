# ---- library definition ----

target_sources(adrtxt_lib
  PUBLIC
  FILE_SET adrtxt_lib_file_set
  TYPE HEADERS FILES
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib.hpp>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/adrtxt/lib.hpp>
  PRIVATE
  lib.cpp
)
target_link_libraries(adrtxt_lib
  PRIVATE
  adrtxt_compile_options
)

# ---- testing ----

if(BUILD_TESTING)
  include(Catch)

  enable_testing()

  find_package(Catch2 REQUIRED)
  add_executable(adrtxt_lib_test)
  target_sources(adrtxt_lib_test
    PRIVATE
    lib.test.cpp
  )
  target_link_libraries(adrtxt_lib_test
    PRIVATE
    adrtxt_lib
    adrtxt_compile_options
    Catch2::Catch2WithMain
  )
  target_precompile_headers(adrtxt_lib_test
    PRIVATE
    <catch2/catch_test_macros.hpp>
  )
  catch_discover_tests(adrtxt_lib_test
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
