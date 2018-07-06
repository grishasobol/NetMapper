#include "net-mapper.hpp"

#include <iostream>

using namespace boost;

NetMapper::NetMapper() {
  using Graph = adjacency_list<vecS, vecS, bidirectionalS>;
  Graph g;
  add_edge(1, 2, g);
  add_edge(3, 2, g);
  add_edge(1, 3, g);
  add_edge(123, 124, g);
  auto index = get(vertex_index, g);
  for (auto vert = vertices(g); vert.first != vert.second; ++vert.first) {
    std::cout << index[*vert.first] << " ";
  }
}
