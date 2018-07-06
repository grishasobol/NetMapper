SET(TEST_LIST TestMapper.cpp)
add_executable(unit-tests ${TEST_LIST})
target_link_libraries(unit-tests gtest gtest_main netmapper)
add_test(UnitTests unit-tests)
