//===- net-mapper.hpp - Network mapper -----------*- C++ -*-===//
//
//===----------------------------------------------------------------------===//
//
// This file define class, that provides functionality to operate with
// undirected simple graph. Graph consist of vertices and edges with weight.
// The main feature is effective search of paths on the graph. Realization relies
// on adjacency_list class from boost graph library and on dijkstra_shortest_paths
// algorithm.
//
//===----------------------------------------------------------------------===//

#ifndef NET_MAPPER_HPP
#define NET_MAPPER_HPP

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"

class VerticesList;
class EdgesList;

/// Network Mapper
class NetMapper final{
public:
  /// Edge weight type
  using WeightType = double;

  /// Type of graph encapsulated realization  
  using Graph = boost::adjacency_list <
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, WeightType>>;

  /// Type of vertex descriptor
  using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;

  /// Type of edge descriptor
  using edge_descriptor = typename boost::graph_traits<Graph>::edge_descriptor;
private:
  Graph graph;

  /// Find all predecessors of pathes to destenation vertex
  /// and store them to cache 
  void find_path(vertex_descriptor dest_vertex) const;

  /// Cache used to store predecessors of pathes to vertex
  mutable std::map<vertex_descriptor, std::vector<vertex_descriptor>> path_preds_cache;

  /// Store cached vertex. If vertex is in, then preds of pathes
  /// can be used.
  mutable std::set<vertex_descriptor> cached_vertices;
public:
  using iter_vert = decltype(boost::vertices(graph).first);
  using iter_edge = decltype(boost::edges(graph).first);

  NetMapper();
  NetMapper(const NetMapper& nm) = delete;
  NetMapper& operator=(const NetMapper& nm) = delete;
  NetMapper(NetMapper&& nm) = delete;
  NetMapper& operator=(NetMapper&& nm) = delete;

  /// Add clean vertex to mapper
  /// @return descriptor of created vertex
  vertex_descriptor add_vertex();

  /// Add edge between to vertices in mapper
  /// If edge already exist, then delete old edge and add the new edge
  /// @param first_vertex
  /// @param second_vertex
  /// @param weight is weight of creating edge
  /// @return descriptor of created edge
  edge_descriptor add_edge(vertex_descriptor first_vertex, 
    vertex_descriptor second_vertex, WeightType weight);

  /// Remove edge from mapper
  /// @param edge is descriptor of the edge
  void remove_edge(edge_descriptor edge);

  /// Remove vertex from mapper
  /// @param vertex is descriptor of the vertex
  void remove_vertex(vertex_descriptor vertex);

  /// @return number of vertices in mapper
  size_t get_vert_num() const;

  /// @return number of edges in mapper
  size_t get_edge_num() const;

  /// Get edge between two vertices
  /// Return flag is true if edge exist, else is false
  /// @param first_vertex
  /// @param second_vertex
  /// @return pair of edge descriptor and flag 
  std::pair<edge_descriptor, bool> get_edge(vertex_descriptor first_vertex, 
    vertex_descriptor second_vertex) const;

  /// @return object allowing itarate over the vertices
  VerticesList get_vertices() const;

  /// @return object allowing itarate over the eges
  EdgesList get_edges() const;

  /// @param edge is descriptor of the edge
  /// @return is weight of the edge
  WeightType get_weight(edge_descriptor edge);

  /// @param dest_vertex is descriptor of destination vertex
  /// @return vector of predecessors of path to destination vertex
  std::vector<vertex_descriptor> get_path_to(vertex_descriptor dest_vertex) const;
};

// TODO: VerticesList and EdgesList could be one template

/// Class that represents functionality to iterate over mapper vertices
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

/// Class that represents functionality to iterate over mapper edges
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
