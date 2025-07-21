cmake_minimum_required(VERSION 3.20)
project(Printers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch GTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# don't override project compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_main
  main.unit.test.cpp
)
target_compile_options(test_main
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wconversion
    -Wshadow
    -Wfloat-equal
    -Wundef
    -Wcast-align
)
target_include_directories(test_main
  PUBLIC
    inc
)
target_link_libraries(test_main
  gtest_main
)

add_executable(main
  main.cpp
)
target_include_directories(main
  PUBLIC
    inc
)
