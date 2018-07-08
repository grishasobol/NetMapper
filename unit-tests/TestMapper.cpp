#include "gtest/gtest.h"
#include "net-mapper.hpp"

#include <vector>
#include <ostream>

class TestMapper : public ::testing::Test
{
protected:
  NetMapper mapper;
};

class TestGraphMapper : public ::testing::Test
{
protected:
  NetMapper mapper;
  using v_desc = NetMapper::vertex_descriptor;
  v_desc v0, v1, v2, v3, v4, v5;
  void SetUp() {
    v0 = mapper.add_vertex();
    v1 = mapper.add_vertex();
    v2 = mapper.add_vertex();
    v3 = mapper.add_vertex();
    v4 = mapper.add_vertex();
    v5 = mapper.add_vertex();
    mapper.add_edge(v0, v1, 10);
    mapper.add_edge(v1, v2, 12);
    mapper.add_edge(v1, v3, 11);
    mapper.add_edge(v2, v4, 13);
    mapper.add_edge(v2, v5, 11);
    mapper.add_edge(v3, v4, 10);
    mapper.add_edge(v3, v5, 10);
    mapper.add_edge(v4, v5, 9);
  }
};

TEST_F(TestMapper, CreateMapper) {
  EXPECT_TRUE(true) << "What???";
}

TEST_F(TestMapper, CheckAddVertices) {
  mapper.add_vertex();
  mapper.add_vertex();
  mapper.add_vertex();
  const size_t vert_num = 3;
  EXPECT_EQ(mapper.get_vert_num(), vert_num);
}

TEST_F(TestGraphMapper, CheckAddEdges) {
  const size_t correct_edges_num = 8;
  EXPECT_EQ(mapper.get_edge_num(), correct_edges_num);
}

TEST_F(TestGraphMapper, CheckPathToVertex1) {
  const std::vector<v_desc> answer = { 0, 0, 1, 1, 3, 3 };
  EXPECT_EQ(answer, mapper.get_path_to(v0));
}

TEST_F(TestGraphMapper, CheckPathToVertex2) {
  const std::vector<v_desc> answer = { 1, 3, 4, 4, 4, 4 };
  EXPECT_EQ(answer, mapper.get_path_to(v4));
}

TEST_F(TestGraphMapper, CheckPathToVertex3) {
  const std::vector<v_desc> answer = { 1, 3, 5, 5, 5, 5 };
  EXPECT_EQ(answer, mapper.get_path_to(v5));
}

TEST_F(TestGraphMapper, CheckPathToAfterChanges) {
  auto dest_vert = v0;
  auto v6 = mapper.add_vertex();
  mapper.add_edge(v0, v6, 2);
  mapper.add_edge(v3, v6, 3);
  mapper.add_edge(v2, v1, 17);
  const std::vector<v_desc> answer = { 0, 0, 5, 6, 3, 3, 0 };
  EXPECT_EQ(answer, mapper.get_path_to(dest_vert));
}

TEST_F(TestGraphMapper, LOL) {
  mapper.remove_vertex(v0);
  size_t correct_edge_num = 7;
  size_t correct_vertices_num = 5;
  EXPECT_EQ(mapper.get_vert_num(), correct_vertices_num);
  EXPECT_EQ(mapper.get_edge_num(), correct_edge_num);
}
