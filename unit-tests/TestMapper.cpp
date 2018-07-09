#include "gtest/gtest.h"
#include "net-mapper.hpp"

#include <vector>
#include <ostream>
#include <string>

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

TEST_F(TestGraphMapper, TestRemoveVertex) {
  mapper.remove_vertex(v0);
  size_t correct_edge_num = 7;
  size_t correct_vertices_num = 5;
  EXPECT_EQ(mapper.get_vert_num(), correct_vertices_num);
  EXPECT_EQ(mapper.get_edge_num(), correct_edge_num);
}

TEST_F(TestGraphMapper, TestRemoveEdge) {
  mapper.remove_edge(mapper.get_edge(v4, v3).first);
  size_t correct_edge_num = 7;
  size_t correct_vertices_num = 6;
  EXPECT_EQ(mapper.get_vert_num(), correct_vertices_num);
  EXPECT_EQ(mapper.get_edge_num(), correct_edge_num);
}

TEST_F(TestGraphMapper, TestGetWeight) {
  double correct_weight = 12;
  EXPECT_EQ(correct_weight, mapper.get_weight(mapper.get_edge(v1, v2).first));
}

TEST_F(TestGraphMapper, CheckPathToVertex1) {
  const std::vector<v_desc> correct_path = { 0, 0, 1, 1, 3, 3 };
  EXPECT_EQ(correct_path, mapper.get_path_to(v0));
}

TEST_F(TestGraphMapper, CheckPathToVertex2) {
  const std::vector<v_desc> correct_path = { 1, 3, 4, 4, 4, 4 };
  EXPECT_EQ(correct_path, mapper.get_path_to(v4));
}

TEST_F(TestGraphMapper, CheckPathToVertex3) {
  const std::vector<v_desc> correct_path = { 1, 3, 5, 5, 5, 5 };
  EXPECT_EQ(correct_path, mapper.get_path_to(v5));
}

TEST_F(TestGraphMapper, CheckPathWithClearVertices) {
  mapper.add_vertex();
  mapper.add_vertex();
  const std::vector<v_desc> correct_path = { 1, 3, 5, 5, 5, 5, 6, 7 };
  EXPECT_EQ(correct_path, mapper.get_path_to(v5));
}

TEST_F(TestGraphMapper, CheckPathToClearVertex) {
  auto v6 = mapper.add_vertex();
  const std::vector<v_desc> correct_path = { 0, 1, 2, 3, 4, 5, 6 };
  EXPECT_EQ(correct_path, mapper.get_path_to(v6));
}

TEST_F(TestGraphMapper, CheckPathAfterRemovingEdge) {
  mapper.remove_edge(mapper.get_edge(v4, v5).first);
  mapper.remove_edge(mapper.get_edge(v4, v3).first);
  const std::vector<v_desc> correct_path = { 0, 0, 1, 1, 2, 3};
  EXPECT_EQ(correct_path, mapper.get_path_to(v0));
}

TEST_F(TestGraphMapper, CheckPathAfterChanges) {
  auto dest_vert = v0;
  auto v6 = mapper.add_vertex();
  mapper.add_edge(v0, v6, 2);
  mapper.add_edge(v3, v6, 3);
  mapper.add_edge(v2, v1, 17);
  const std::vector<v_desc> answer = { 0, 0, 5, 6, 3, 3, 0 };
  EXPECT_EQ(answer, mapper.get_path_to(dest_vert));
}

TEST_F(TestGraphMapper, CheckGetNextVert) {
  EXPECT_EQ(mapper.get_next_vert(v5, v0), v3);
  EXPECT_EQ(mapper.get_next_vert(v4, v0), v3);
  mapper.add_edge(v0, v5, 3);
  EXPECT_EQ(mapper.get_next_vert(v5, v0), v0);
  mapper.add_edge(v0, v4, 3);
  EXPECT_EQ(mapper.get_next_vert(v4, v0), v0);
}

TEST_F(TestGraphMapper, TestVerticesList) {
  std::string correct_vertices = "0 1 2 3 4 5 ";
  std::string vertices;
  for (auto vert : mapper.get_vertices()) {
    vertices += std::to_string(vert) + " ";
  }
  EXPECT_EQ(correct_vertices, vertices);
}

TEST_F(TestGraphMapper, TestEdgesList) {
  double correct_sum = 86;
  double sum = 0;
  for (auto edge : mapper.get_edges()) {
    sum += mapper.get_weight(edge);
  }
  EXPECT_EQ(correct_sum, sum);
}

TEST_F(TestGraphMapper, GetNoExistEdge) {
  EXPECT_FALSE(mapper.get_edge(v0, v5).second);
}


// Crash assertion tests only in debug mode
#ifndef NDEBUG

TEST_F(TestGraphMapper, OutOfRangeGetEdge) {
  EXPECT_DEBUG_DEATH(mapper.get_edge(100, 101), "");
}

TEST_F(TestGraphMapper, OutOfRangeAddEdge) {
  EXPECT_DEBUG_DEATH(mapper.add_edge(100, 101, 10), "");
}

TEST_F(TestGraphMapper, OutOfRangeRemoveVertex) {
  EXPECT_DEBUG_DEATH(mapper.remove_vertex(100), "");
}

TEST_F(TestGraphMapper, RemoveNoExistEdge) {
  EXPECT_DEBUG_DEATH(mapper.remove_edge(mapper.get_edge(v0, v5).first), "");
}

TEST_F(TestGraphMapper, GetWeightNoExistEdge) {
  EXPECT_DEBUG_DEATH(mapper.get_weight(mapper.get_edge(v0, v5).first), "");
}

TEST_F(TestGraphMapper, GetPathToNoExistVertex) {
  EXPECT_DEBUG_DEATH(mapper.get_path_to(100), "");
}

#endif // DEBUG
