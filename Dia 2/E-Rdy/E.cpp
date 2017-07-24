#include <cstddef> // size_t
#include <iostream>
#include <limits> // numeric_limits
#include <vector>

using std::cin;
using std::cout;
using std::size_t;

/*
CLASS
*/
class directed_graph {
  std::vector<std::vector<size_t>> outedges, inedges;
  std::vector<std::pair<size_t, size_t>> edge_list;

public:
  explicit directed_graph(size_t n_verts)
      : outedges(n_verts), inedges(n_verts) {}

  size_t add_edge(size_t src, size_t tgt) {
    edge_list.emplace_back(src, tgt);
    const size_t edge_id = edge_list.size() - 1;
    outedges[src].push_back(edge_id);
    inedges[tgt].push_back(edge_id);
    return edge_id;
  }

  size_t num_vertices() const { return outedges.size(); }
  size_t num_edges() const { return edge_list.size(); }

  size_t source(size_t e) const { return edge_list[e].first; }
  size_t target(size_t e) const { return edge_list[e].second; }

  const std::vector<size_t> &out_edges(size_t v) const { return outedges[v]; }
  const std::vector<size_t> &in_edges(size_t v) const { return inedges[v]; }

  size_t out_degree(size_t v) const { return outedges[v].size(); }
  size_t in_degree(size_t v) const { return inedges[v].size(); }
};

/*
FUNCTIONS
*/

template <typename Graph, typename Distance>
bool bellman_ford(const Graph &g, const size_t source,
                  const std::vector<Distance> &weight,
                  std::vector<Distance> &dist) {
  const auto infinity = std::numeric_limits<Distance>::max();
  const size_t num_edges = g.num_edges();

  dist.assign(g.num_vertices(), infinity);
  dist[source] = 0;

  for (size_t step = 0; step != dist.size(); ++step) {
    bool updated = false;

    for (size_t e = 0; e != num_edges; ++e) {
      if (dist[g.source(e)] == infinity)
        continue;
      if (dist[g.source(e)] + weight[e] >= dist[g.target(e)])
        continue;
      // pred[g.target(e)] = g.source(e);
      dist[g.target(e)] = dist[g.source(e)] + weight[e];
      updated = true;
    }
    if (!updated)
      return true;
  }
  return false;
}

template <class Function> void repeat(std::size_t n, Function f) {
  while (n--)
    f();
}

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  repeat(input<size_t>(), [&] {
    auto n = input<size_t>();
    auto m = input<size_t>();
    directed_graph graph(n);
    std::vector<int> weight_vec(m);
    std::vector<int> dist_vec;

    repeat(m, [&] {
      auto x = input<int>();
      auto y = input<int>();
      auto wght = input<int>();

      weight_vec[graph.add_edge(x, y)] = wght;
    });

    if (!bellman_ford(graph, 1, weight_vec, dist_vec))
      cout << "possible\n";
    else
      cout << "not possible\n";
  });
  return 0;
}
