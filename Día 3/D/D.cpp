// Utilities library
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

using matrix = std::vector<std::vector<int>>;
using array = std::vector<int>;

// Support code
using std::cout;
using std::cin;
using std::size_t;


template <class Function>
void repeat(std::size_t n, Function f) {
    while(n--) f();
}

template <class T>
T input_value(std::istream& input = std::cin) {
    T value;
    input >> value;
    return value;

  }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto N = input_value<int>();
  repeat( N ,[&]{
    auto cant_of_money = input_value<int>();
    array moneys(cant_of_money);
    matrix memoized(2,array(cant_of_money));
    for( auto &elem : moneys)
      cin>>elem;
    std::cout << "cant_of_money : "<< cant_of_money << '\n';
    for(const auto &elem : moneys)
      std::cout << "\t"<<elem<<"\t";
    std::cout << '\n';
  });
}
