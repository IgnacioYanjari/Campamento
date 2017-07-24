#include <cstddef> // size_t
#include <iostream>
#include <limits>  // numeric_limits
#include <queue>   // priority_queue
#include <utility> // pair
#include <vector>  // vector

using std::cin;
using std::cout;
using std::size_t;

/*
CLASSES
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
template <class Graph, class Distance>
std::vector<std::pair<size_t, size_t>>
dijkstra(const Graph &g, size_t source, const std::vector<Distance> &weight) {

  struct pq_elem {
    Distance dist;
    size_t vertex;
    bool operator<(const pq_elem &that) const { return dist > that.dist; }
  };

  std::vector<std::pair<size_t, size_t>> paths;
  std::vector<bool> visited(g.num_vertices(), false);
  std::vector<Distance> dist(g.num_vertices(),
                             std::numeric_limits<Distance>::max());

  std::priority_queue<pq_elem> pq;
  pq.push({dist[source] = 0, source});

  while (!pq.empty()) {
    const size_t u = pq.top().vertex;
    pq.pop();
    if (visited[u])
      continue;

    visited[u] = true;

    for (const auto edge : g.out_edges(u)) {
      const size_t v = g.target(edge);
      const Distance alt = dist[u] + weight[edge]; // alternative
      if (alt < dist[v]) {
        pq.push({dist[v] = alt, v});
        paths.push_back({u + 1, alt});
      }
    }
  }
  return paths;
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

  auto n = input<size_t>();
  auto m = input<size_t>();

  directed_graph graph(n);
  std::vector<size_t> weight_of(m);

  repeat(m, [&] {
    auto x = input<size_t>();
    auto y = input<size_t>();
    auto wght = input<size_t>();

    weight_of[graph.add_edge(x - 1, y - 1)] = wght;
  });

  const auto paths = dijkstra(graph, 0, weight_of);

  for (auto &elem : paths)
    cout << elem.first << ' ' << elem.second << '\n';

  return 0;
}
