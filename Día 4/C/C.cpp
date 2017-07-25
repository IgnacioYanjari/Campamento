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
  dgraph(size_t n_verts) : outedges(n_verts), inedges(n_verts) {}

  size_t add_edge(size_t from, size_t to) {
    edge_list.emplace_back(from, to);
    const size_t edge_id = edge_list.size() - 1;
    outedges.at(from).push_back(edge_id);
    inedges.at(to).push_back(edge_id);
    return edge_id;
  }

  int last_edge_inserted() {
    if (is_empty())
      return -1;
    return edge_list.at(edge_list.size() - 1).second;
  }

private:
  bool is_empty() {
    if (edge_list.size() == 0)
      return true;
    return false;
  }

private:
  std::unordered_map<> edge_list;
  std::vector<std::vector<size_t>> outedges, inedges;
};

// FUNCTIONS

template <class Function> void repeat(std::size_t n, Function f) {
  while (n--)
    f();
}

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

void make_letter_graph(dgraph &gp, std::string &str1, std::string &str2) {
  if (str1.at(0) != str2.at(0)) {
    if (gp.last_edge_inserted() == -1)
      gp.add_edge(str1.at(0) - 'A', str2.at(0) - 'A');
    else
      gp.add_edge(gp.last_edge_inserted(), str2.at(0) - 'A');
    // return true;
  } else {
    for (size_t i = 1; i < str1.size() && i < str2.size(); ++i) {
      if (str1.at(i) != str2.at(i)) {
        if (gp.last_edge_inserted() == -1)
          gp.add_edge(str1.at(i) - 'A', str2.at(i) - 'A');
        else
          gp.add_edge(gp.last_edge_inserted(), str2.at(i) - 'A');
        // gp.add_edge(str1.at(i) - 'A', str2.at(i) - 'A');
        break;
      } else {
        continue;
      }
    }

    size_t pos = str1.size();

    if (pos > str2.size())
      pos = str2.size();
    gp.add_edge(gp.last_edge_inserted(), str2.at(pos) - 'A');
  }
}

// Program code

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string str;
  std::vector<std::string> str_input;
  std::unordered_set<char> letter_map;

  while (cin >> str && str != "#") {
    str_input.push_back(str);

    for (auto &letter : str) {
      if (letter_map.find(letter) != letter_map.end())
        continue;
      else
        letter_map.insert(letter);
    }
  }

  size_t gpsize = letter_map.size();
  dgraph graph(gpsize);

  for (auto &elem : str_input)
    cout << elem << '\n';

  for (size_t ix = 1; ix < str_input.size(); ++ix) {
    make_letter_graph(graph, str_input.at(ix - 1), str_input.at(ix));
  }

  // graph.print_graph();

  return 0;
}
