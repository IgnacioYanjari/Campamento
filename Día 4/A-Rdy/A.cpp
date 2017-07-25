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

bool cycle_check( std::vector< std::vector<size_t> > graph , std::vector<size_t> marked , size_t in  ){
  std::stack< std::pair<size_t,size_t>> pila;
  pila.push(std::make_pair(in,-1));
  marked.at(in) = 1;
  //std::cout << "in : "<<in << '\n';
  while( !pila.empty() ){
    auto now = pila.top();
    //std::cout << "now : "<<now.first<<"\n";
    pila.pop();
    for (size_t i = 0; i < marked.size(); i++) {
      if( graph.at(now.first).at(i) == 1 && now.second != i){
        if(marked.at(i) == 0){
            marked.at(i)=1;
            pila.push(std::make_pair(i,now.first));
          }
          else{
            //std::cout << " GG i : "<<i<<" now :"<<now.first<< '\n';
            return true;
          }
        }
    }
  }
 return false;
}

size_t dp1( std::vector< std::vector<size_t> > graph , std::vector<size_t> marked , size_t in ){
  std::stack<size_t> pila;
  pila.push(in);
  marked.at(in) = 1;
  size_t sum=1;
  while( !pila.empty() ){
    auto now = pila.top();
    pila.pop();
    for (size_t i = 0; i < marked.size(); i++) {
      if( graph.at(now).at(i) == 1){
        if(marked.at(i) == 0){
            marked.at(i)=1;
            pila.push(i);
            sum++;
          }
        }
    }
  }
  return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto N = input_value<size_t>();
    auto M = input_value<size_t>();
    std::vector< std::vector<size_t> > graph( N , std::vector<size_t>(N) );
    std::vector<size_t> marked(N);
    size_t x,y;
    for (size_t i = 0; i < M ; i++) {
      cin>>x>>y;
      graph.at(x-1).at(y-1) = 1;
      graph.at(y-1).at(x-1) = 1;
    }
    if (N < 3 || N != M){
      std::cout << "NO" << '\n';
      return 0;
    }
    if ( dp1(graph,marked,0) == N ){
      auto check = cycle_check(graph,marked,0);
      if(check)
        std::cout << "FHTAGN!" << '\n';
      else
        std::cout<<"NO"<< '\n';
    }
    else
      std::cout << "NO" << '\n';
}
