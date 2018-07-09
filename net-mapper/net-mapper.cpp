#include "net-mapper.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <ostream>

using namespace boost;
using v_desc = NetMapper::vertex_descriptor;
using e_desc = NetMapper::edge_descriptor;

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
  assert(first_vertex < get_vert_num() && second_vertex < get_vert_num()
    && "vertices descriptors is out of range");
  auto exist_edge = get_edge(first_vertex, second_vertex);
  if (exist_edge.second) {
    remove_edge(exist_edge.first);
  }
  cached_vertices.clear();
  return boost::add_edge(first_vertex, second_vertex, weight, graph).first;
}

void NetMapper::remove_edge(NetMapper::edge_descriptor edge) {
  cached_vertices.clear();
  boost::remove_edge(edge, graph);
}

void NetMapper::remove_vertex(NetMapper::vertex_descriptor vertex) {
  cached_vertices.clear();
  boost::clear_vertex(vertex, graph);
  boost::remove_vertex(vertex, graph);
}

size_t NetMapper::get_vert_num() const {
  return num_vertices(graph);
}

size_t NetMapper::get_edge_num() const {
  return num_edges(graph);
}

std::pair<e_desc, bool> NetMapper::get_edge(v_desc first_vertex,
  v_desc second_vertex) const {
  return boost::edge(first_vertex, second_vertex, graph);
}

VerticesList NetMapper::get_vertices() const {
  auto verts = boost::vertices(graph);
  return VerticesList(verts.first, verts.second);
}

EdgesList NetMapper::get_edges() const {
  auto edges = boost::edges(graph);
  return EdgesList(edges.first, edges.second);
}

NetMapper::WeightType NetMapper::get_weight(e_desc edge) {
  return boost::get(boost::edge_weight_t(), graph, edge);
}

std::vector<NetMapper::vertex_descriptor> 
NetMapper::get_path_to(NetMapper::vertex_descriptor dest_vertex) const {
  if (cached_vertices.find(dest_vertex) == cached_vertices.end()) {
    find_path(dest_vertex);
  }
  return path_preds_cache[dest_vertex];
}

v_desc NetMapper::get_next_vert(v_desc source_vert, v_desc dest_vert) const {
  return get_path_to(dest_vert)[source_vert];
}

