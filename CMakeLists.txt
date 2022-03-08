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
message("Added solver library with name ${PROJECT_CORE_LIB_NAME}")

# Enable generating coverage report in testing process
option(COVERAGE "Enable generating coverage report" OFF)
if (COVERAGE)
    message("Enabled code coverage report generation")
    target_compile_options(${PROJECT_CORE_LIB_NAME} PUBLIC "--coverage")
    target_link_libraries(${PROJECT_CORE_LIB_NAME} PUBLIC gcov)
endif ()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_LIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_CORE_LIB_NAME})
message("Created app target with name ${PROJECT_NAME}")

# This part of provides testing with gtest Google C++ Testing Framework
option(TEST "Enable testing" OFF)
if (TEST)
    message("Enabled testing")
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    message("Google C++ Testing Framework loaded")

    file(GLOB SolverTestsSRC "tests/solver/*.cpp")
    file(GLOB InterfaceTestsSRC "tests/interface/*.cpp")
    set(testing_targets)
    foreach (file IN ITEMS ${SolverTestsSRC})
        message("${file} TEST FILE FOUND")
        get_filename_component(testing_target ${file} NAME_WE)
        add_executable(${testing_target} ${file})
        target_link_libraries(${testing_target} gtest_main)
        target_link_libraries(${testing_target} ${PROJECT_CORE_LIB_NAME})
        message("${testing_target} TARGET CREATED")
        set(testing_targets ${testing_targets};${testing_target})
    endforeach ()

    message("TESTING TARGETS TOTAL: ${testing_targets}")

    include(GoogleTest)
    foreach (target IN ITEMS ${testing_targets})
        target_compile_options(${target} PUBLIC -fsanitize=address)
        target_link_options(${target} PUBLIC -fsanitize=address)
        gtest_discover_tests(${target})
    endforeach ()
endif ()

# This part of provides clang-tidy code analise
option(LINTERS-CHECK "Enable clang-tidy check" OFF)
if (LINTERS-CHECK)
    message("Enabled clang-tidy sources check")
    set(SOURCES ../project/src/solver.c ../project/main.c)

    add_custom_target(
            clang-tidy-check-code clang-tidy -p ${CMAKE_BINARY_DIR}/compile_commands.json  ${SOURCES}
            DEPENDS ${SOURCES}
    )
    add_custom_target(infer-check infer run --compilation-database compile_commands.json)

    add_custom_target(linter-check DEPENDS clang-tidy-check-code infer-check)
endif ()
