#ifndef NET_MAPPER_HPP
#define NET_MAPPER_HPP

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"

class NetMapper{
public:
  NetMapper();
  NetMapper(const NetMapper& nm) = delete;
  NetMapper& operator=(const NetMapper& nm) = delete;
};

#endif
