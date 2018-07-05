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

SET(TEST_LIST TestMapper.cpp)

add_executable(unit-tests ${TEST_LIST})
target_link_libraries(unit-tests gtest gtest_main)
add_test(UnitTests unit-tests)
