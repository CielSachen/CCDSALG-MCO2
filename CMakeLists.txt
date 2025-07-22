cmake_minimum_required(VERSION 3.15...4.0)

project(ConvexHull
  VERSION 1.0.0
  DESCRIPTION "The second major course output (MCO2) for CCDSALG."
  HOMEPAGE_URL "https://github.com/CielSachen/CCDSALG-MCO2#readme"
  LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_subdirectory(src)
add_subdirectory(app)
