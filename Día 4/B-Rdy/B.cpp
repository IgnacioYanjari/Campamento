#include <cstdlib>
#include <bitset>
#include <functional>
#include <utility>
#include <tuple>
#include <limits>
#include <cinttypes>
#include <cassert>
// Strings library
#include <cctype>
#include <cstring>
#include <string>
//Containers library
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
// Algorithms library
#include <algorithm>
// Iterators library
#include <iterator>
// Numerics library
#include <cmath>
#include <complex>
#include <valarray>
#include <numeric>
// Input/Ouput library
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
// Localization library
#include <locale>
// Regular expressions library
#include <regex>

using std::size_t;
using std::cin;
using std::cout;

// Support code
//CLASS
class undirected_graph {
  std::vector<std::vector<size_t>> adj_edges;
  std::vector<std::pair<size_t, size_t>> edge_list;

public:
  explicit undirected_graph(size_t num_vertices) : adj_edges(num_vertices) {}

  size_t add_edge(size_t u, size_t v) {
    edge_list.emplace_back(u, v);
    const size_t edge_id = edge_list.size() - 1;
    adj_edges[u].push_back(edge_id);
    adj_edges[v].push_back(edge_id);
    return edge_id;
  }

  size_t num_vertices() const {
    return adj_edges.size();
  }
  size_t num_edges() const {
    return edge_list.size();
  }

  size_t source(size_t e) const {
    return edge_list[e].first;
  }
  size_t target(size_t e) const {
    return edge_list[e].second;
  }

  const std::vector<size_t>& out_edges(size_t v) const {
    return adj_edges[v];
  }
  const std::vector<size_t>& in_edges(size_t v) const {
    return adj_edges[v];
  }

  size_t degree(size_t v) const {
    return adj_edges[v].size();
  }
  size_t out_degree(size_t v) const {
    return degree(v);
  }
  size_t in_degree(size_t v) const {
    return degree(v);
  }
};


class disjoint_set {
  std::unique_ptr<size_t[]> parent, rank;

public:
  explicit disjoint_set(size_t n) : parent(new size_t[n]), rank(new size_t[n]) {
    for (size_t x = 0; x != n; ++x) {
      parent[x] = x;
      rank[x] = 0;
    }
  }

  size_t find_set(size_t x) {
    if (parent[x] != x)
      parent[x] = find_set(parent[x]);
    return parent[x];
  }

  bool union_set(size_t x, size_t y) {
    x = find_set(x);
    y = find_set(y);
    if (x == y)
      return false;

    if (rank[x] > rank[y]) {
      parent[x] = y;
    } else if (rank[x] < rank[y]) {
      parent[y] = x;
    } else {
      parent[y] = x;
      ++rank[x];
    }
    return true;
  }
};

//FUNCTIONS
template <typename Graph, typename Weight>
std::vector<size_t>
m_spanning_tree(const Graph& g,
                              const std::vector<Weight>& weight) {
  const size_t num_vertices = g.num_vertices();
  if (num_vertices == 0)
    return {};

  std::vector<size_t> edges(g.num_edges());
  std::iota(edges.begin(), edges.end(), size_t{0});

  std::sort(edges.begin(), edges.end(),
            [&](size_t lhs, size_t rhs) { return weight[lhs] < weight[rhs]; });

  disjoint_set dset(num_vertices);

  const size_t max_tree_edges = num_vertices - 1;
  std::vector<size_t> tree_edges;
  tree_edges.reserve(max_tree_edges);

  for (const auto e : edges) {
    if (dset.union_set(g.source(e), g.target(e))) {
      tree_edges.push_back(e);
      if (tree_edges.size() == max_tree_edges)
        break;
    }
  }

  return tree_edges;
}



template <class Function>
void repeat(std::size_t n, Function f) {
    while(n--) f();
}

template <class T>
T input(std::istream& input = std::cin) {
    T value;
    input >> value;
    return value;
}

// Program code

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;

    while (cin >> n >> m){
        if (n == 0 && m == 0)
            break;

        undirected_graph graph(n);
        std::vector<size_t> weight_of(m);
        size_t weight_total_sum = 0;

        repeat(m, [&]{
            auto x = input<size_t>();
            auto y = input<size_t>();
            auto wght = input<size_t>();
            weight_total_sum += wght;

            weight_of[graph.add_edge(x, y)] = wght;
        });

        const auto mst_edges = m_spanning_tree(graph, weight_of);
        size_t sum = 0;

        for (size_t ix = 0; ix < mst_edges.size(); ++ix){
            sum += weight_of[mst_edges[ix]];
        }

        cout << weight_total_sum - sum << '\n';

    }


    return 0;
}
