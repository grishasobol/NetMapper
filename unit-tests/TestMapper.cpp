#include "gtest/gtest.h"
#include "net-mapper.hpp"

class TestMapper : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
};

TEST_F(TestMapper, EmptyTest){
	EXPECT_TRUE(true) << "What???";
}

TEST_F(TestMapper, CreateMapper) {
  NetMapper mapper;
  EXPECT_TRUE(true) << "What???";
}
