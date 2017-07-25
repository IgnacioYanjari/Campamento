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

int dp_bottom(std::vector< std::vector<int> > graph, std::vector<int> &memoized, int m, std::map<int, bool> map){
  memoized.at(m) = 1;
  for(int j = m-1 ; j >=0 ;j--){
    int suma=0;
    for(int i = m; i >= 0 ;i--){
      if( graph.at(i).at(j) == 1 ){
        suma+=memoized.at(i);
      }
    }
    memoized.at(j) = suma;
  }
  return memoized.at(0);
}

int dp_top_down(std::vector< std::vector<int> > graph, std::vector<int> &memoized, int m, std::map<int, bool> map){
  if(memoized)
  memoized.at(m) = 1;
  for(int j = m-1 ; j >=0 ;j--){
    int suma=0;
    for(int i = m; i >= 0 ;i--){
      if( graph.at(i).at(j) == 1 ){
        suma+=memoized.at(i);
      }
    }
    memoized.at(j) = suma;
  }
  return memoized.at(0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int  N;
    bool first = true;
    while(cin>>N){
      if(!first)
        cout<<"\n";
      else
        first = false;
      std::map<int,bool> map;
      std::vector< std::vector<int> > graph( N+1 , std::vector<int>(N+1) );
      std::vector<int > memoized( N+1 );
      for (int i = 0; i < N; i++) {
        auto K = input_value<int>();
        if( K == 0){
          map[i] = true;
        }
        for (int j = 0; j < K; j++) {
          auto node = input_value<int>();
          graph.at(node).at(i)=1;
        }
      }
      for (auto &elem : map) {
        graph.at(N).at(elem.first)=1;
      }
      std::cout<<  dp_bottom(graph,memoized,N,map)<<"\n";
    }
}
