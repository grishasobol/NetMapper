cmake_minimum_required(VERSION 3.6)
project(NetMapper)
include_directories(include)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_CXX_STANDARD 14)
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

if(NOT GTEST_DIR)
	message(FATAL_ERROR "Please, define googletests source directory")
ENDIF()

include(${GTEST_DIR}/googletest/cmake/internal_utils.cmake)

enable_testing()
include_directories(${GTEST_DIR}/googletest/include)
config_compiler_and_linker()

#TODO make testing optional
SET(BUILD_GMOCK OFF CACHE BOOL "Enable gmock build" FORCE)
SET(BUILD_GTEST ON CACHE BOOL  "Enable gtest build" FORCE)
add_subdirectory(${GTEST_DIR} gtest)

add_subdirectory(net-mapper)
add_subdirectory(unit-tests)
