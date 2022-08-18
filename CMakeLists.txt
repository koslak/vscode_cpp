cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

project(
    zero 
    VERSION 0.1.0
    DESCRIPTION "zero application description"
    LANGUAGES CXX
)

if (MSVC)
    # Disable annoying secure CRT warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")

    # Parallel build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP24")

    # Enable more warnings
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    # Disable warnings that are present in dependencies and irrelevant to us
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100") # unused arguments
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5054") # deprecated enum & operator
endif()

set(PROJECT_SOURCES
    src/main.cpp
)

set(TEST_SOURCES
    src/tests/tests/tests.cpp
    src/tests/tests/main.cpp
)

set(BENCHMARK_SOURCES
    src/tests/benchmarks/benchmark_test_1.cpp
    src/tests/benchmarks/benchmark_test_2.cpp
    src/tests/benchmarks/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)  # Not sure if this works but I'm including it here.

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.x)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark
FetchContent_MakeAvailable(googletest googlebenchmark)

# Tests Executable:
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests gtest)

# Benchmarks Executable:
add_executable(${PROJECT_NAME}_benchmarks ${BENCHMARK_SOURCES})
target_link_libraries(${PROJECT_NAME}_benchmarks benchmark::benchmark)
