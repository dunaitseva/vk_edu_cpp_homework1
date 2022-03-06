cmake_minimum_required(VERSION 3.16)
PROJECT(HW1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Werror -Wextra -Wpedantic -Wall")

set(PROJECT_NAME parabola_builder)

set(PROJECT_SOURCE_DIR project)
set(PROJECT_LIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_LIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.c)