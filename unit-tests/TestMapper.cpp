#include "gtest/gtest.h"

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
