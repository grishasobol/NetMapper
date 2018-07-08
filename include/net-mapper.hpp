#ifndef NET_MAPPER_HPP
#define NET_MAPPER_HPP

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"

#include <type_traits>

class VerticesList;
class EdgesList;

class NetMapper final{
public:
  using WeightType = double;
  using Graph = boost::adjacency_list <
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, WeightType>>;
  using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;
  using edge_descriptor = typename boost::graph_traits<Graph>::edge_descriptor;
private:
  Graph graph;
  void find_path(vertex_descriptor dest_vertex) const;
  mutable std::map<vertex_descriptor, std::vector<vertex_descriptor>> path_preds_cache;
  mutable std::set<vertex_descriptor> cached_vertices;
public:
  using iter_vert = decltype(boost::vertices(graph).first);
  using iter_edge = decltype(boost::edges(graph).first);

  NetMapper();
  NetMapper(const NetMapper& nm) = delete;
  NetMapper& operator=(const NetMapper& nm) = delete;
  NetMapper(NetMapper&& nm) = delete;
  NetMapper& operator=(NetMapper&& nm) = delete;

  vertex_descriptor add_vertex();
  edge_descriptor add_edge(vertex_descriptor first_vertex, 
    vertex_descriptor second_vertex, WeightType weight);
  void remove_edge(edge_descriptor edge);
  void remove_vertex(vertex_descriptor vertex);

  size_t get_vert_num() const;
  size_t get_edge_num() const;
  std::pair<edge_descriptor, bool> get_edge(vertex_descriptor first_vertex, 
    vertex_descriptor second_vertex) const;
  VerticesList get_vertices() const;
  EdgesList get_edges() const;
  std::vector<vertex_descriptor> get_path_to(vertex_descriptor dest_vertex) const;
};

class VerticesList {
  const NetMapper::iter_vert _begin;
  const NetMapper::iter_vert _end;
public:
  VerticesList(const NetMapper::iter_vert begin, const NetMapper::iter_vert end) : 
    _begin(begin), _end(end) {}
  NetMapper::iter_vert begin() const {
    return _begin;
  }
  NetMapper::iter_vert end() const {
    return _end;
  }
};

class EdgesList {
  const NetMapper::iter_edge _begin;
  const NetMapper::iter_edge _end;
public:
  EdgesList(const NetMapper::iter_edge begin, const NetMapper::iter_edge end) :
    _begin(begin), _end(end) {}
  NetMapper::iter_edge begin() const {
    return _begin;
  }
  NetMapper::iter_edge end() const {
    return _end;
  }
};

#endif
