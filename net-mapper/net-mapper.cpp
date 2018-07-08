#include "net-mapper.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace boost;

NetMapper::NetMapper() {}

void NetMapper::find_path(vertex_descriptor dest_vertex) const {
  using IdMap = typename boost::property_map<Graph, boost::vertex_index_t>::type;
  using preds_map_t = boost::iterator_property_map<std::vector<vertex_descriptor>::iterator,
    IdMap,
    vertex_descriptor,
    vertex_descriptor&>;

  std::vector<vertex_descriptor> path_preds(num_vertices(graph));
  preds_map_t predmap(path_preds.begin(), get(boost::vertex_index, graph));
  dijkstra_shortest_paths(graph, dest_vertex, predecessor_map(predmap));

  path_preds_cache.insert(std::make_pair(dest_vertex, std::move(path_preds)));
  cached_vertices.insert(dest_vertex);
}

NetMapper::vertex_descriptor NetMapper::add_vertex() {
  return boost::add_vertex(graph);
}


NetMapper::edge_descriptor NetMapper::add_edge(vertex_descriptor first_vertex, 
  vertex_descriptor second_vertex, WeightType weight) {
  return boost::add_edge(first_vertex, second_vertex, weight, graph).first;
}

size_t NetMapper::get_vert_num() const {
  return num_vertices(graph);
}

size_t NetMapper::get_edge_num() const {
  return num_edges(graph);
}

std::vector<NetMapper::vertex_descriptor> 
NetMapper::get_path_to(NetMapper::vertex_descriptor dest_vertex) const {
  if (cached_vertices.find(dest_vertex) == cached_vertices.end()) {
    find_path(dest_vertex);
  }
  return path_preds_cache[dest_vertex];
}