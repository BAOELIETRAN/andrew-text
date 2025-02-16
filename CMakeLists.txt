include(cmake/no-insource.cmake)
cmake_minimum_required(VERSION 3.28.0)
project(template
    VERSION 0.1.0
    HOMEPAGE_URL "https://example.com"
    DESCRIPTION "Another CMake template"
    LANGUAGES CXX)

include(cmake/top-level.cmake)
include(cmake/compile-options.cmake)
include(cmake/folders.cmake)

# ---- library ----

# target_sources inside the src/ directory

add_library(template_lib)
target_include_directories(template_lib ${WARNING_GUARD}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)
add_library(template::template ALIAS template_lib)

include(CMakeDependentOption)
cmake_dependent_option(template_DEV "Enable if you plan to work on this project"
    OFF "PROJECT_IS_TOP_LEVEL" OFF
)

add_subdirectory(src)
add_subdirectory(tests)
if(template_DEV)
  include(cmake/docs.cmake)
endif()
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install.cmake)
endif()
