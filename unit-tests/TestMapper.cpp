#include "gtest/gtest.h"
#include "net-mapper.hpp"

class TestMapper : public ::testing::Test
{
protected:
  NetMapper mapper;
};

class TestGraphMapper : public ::testing::Test
{
protected:
  NetMapper mapper;
  void SetUp() {

  }
};

TEST_F(TestMapper, CreateMapper) {
  EXPECT_TRUE(true) << "What???";
}

TEST_F(TestMapper, CheckAddVertices) {
  mapper.add_vertex();
  mapper.add_vertex();
  mapper.add_vertex();
  mapper.add_vertex();
  EXPECT_TRUE(mapper.get_vert_num() == 4) 
    << "Excpect 4 verteces, but get: " 
    << mapper.get_vert_num();
}

TEST_F(TestMapper, CheckAddEdges) {
  auto v0 = mapper.add_vertex();
  auto v1 = mapper.add_vertex();
  auto v2 = mapper.add_vertex();
  auto v3 = mapper.add_vertex();
  auto e1 = mapper.add_edge(v0, v1, 10);
  auto e2 = mapper.add_edge(v0, v2, 11);
  auto e3 = mapper.add_edge(v0, v3, 12);
  EXPECT_TRUE(mapper.get_edge_num() == 3) 
    << "Excpect 3 edges, but get: "
    << mapper.get_edge_num();
}
