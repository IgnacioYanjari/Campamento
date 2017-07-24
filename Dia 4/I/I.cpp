#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cinttypes>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <forward_list>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

// Support code

using std::size_t;
using std::cin;
using std::cout;

// CLASS
class dgraph {
public:
  dgraph(size_t n_verts)
      : adj_list(n_verts, std::pair<std::vector<size_t>(), 0>) {}

  size_t add_edge(size_t src, size_t trg) { adj_list.at(src).push_back(trg); }

private:
  std::vector<std::pair<std::vector<size_t>, size_t>> adj_list;
}

// FUNCTIONS

template <class Function>
void repeat(std::size_t n, Function f) {
  while (n--)
    f();
}

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

// Program code

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto n = input<size_t>();
  dgraph graph(n);
  std::vector<size_t> cost;

  repeat(n, [&] {
    size_t val = input<size_t>();
    cost.push_back(val);
  });

  auto m = input<size_t>();
  for (size_t ix = 0; ix < m; ++ix) {
    auto x = input<size_t>();
    auto y = input<size_t>();

    graph.add_edge(x, y);
  }

  for (auto &elem : cost)
    cout << elem << " ";

  return 0;
}
