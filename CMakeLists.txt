cmake_minimum_required(VERSION 3.16)
PROJECT(HW1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Werror -Wextra -Wpedantic -Wall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

set(PROJECT_NAME parabola_builder)

set(PROJECT_SOURCE_DIR project)
set(PROJECT_LIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_LIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_CORE_LIB_NAME parabola_solver)

add_library(${PROJECT_CORE_LIB_NAME} ${PROJECT_LIB_SOURCE_DIR}/solver.c)
target_include_directories(${PROJECT_CORE_LIB_NAME} PUBLIC ${PROJECT_LIB_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_LIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_CORE_LIB_NAME})

# This part of provides testing with gtest Google C++ Testing Framework
option(TEST "Enable testing" OFF)
if (TEST)

    # Enable generating coverage report in testing process
    option(COVERAGE "Enable generating coverage report" OFF)
    if (COVERAGE)
    target_compile_options(${PROJECT_CORE_LIB_NAME} PUBLIC "--coverage")
    target_link_libraries(${PROJECT_CORE_LIB_NAME} PUBLIC gcov)
    endif()

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(solver_test tests/SolverTests.cpp)
    target_link_libraries(solver_test gtest_main)
    target_link_libraries(solver_test ${PROJECT_CORE_LIB_NAME})
    target_include_directories(solver_test PUBLIC ${PROJECT_LIB_INCLUDE_DIR})

    include(GoogleTest)
    gtest_discover_tests(solver_test)
endif ()

# This part of provides clang-tidy code analise
option(TIDY-CHECK "Enable clang-tidy check" OFF)
if (TIDY-CHECK)
    set(SOURCES ../project/src/solver.c ../project/main.c)

    add_custom_target(
            clang-tidy-check-code clang-tidy -p ${CMAKE_BINARY_DIR}/compile_commands.json ${CLANG_TIDY_FLAGS} ${SOURCES}
            DEPENDS ${SOURCES}
    )

    add_custom_target(clang-tidy-check DEPENDS clang-tidy-check-code)
endif ()