#include <iostream>
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
using namespace std;

template <class T>
class dwgraph{

  public:
    using edge_t = std::pair<T,T>;
    using list_edge_t = std::vector<edge_t>;

  public:
    dwgraph(T size) : list_adj(size,list_edge_t()){}
    void connect( T from , T to , T weight = 1 ){
      list_adj.at(from).push_back({to,weight});
    }
    list_edge_t get(T v){
      return list_adj[v];
    }

  private:
    std::vector<list_edge_t> list_adj;
};

template <class T>
T input_value(std::istream& input = std::cin) {
    T value;
    input >> value;
    return value;
}

int main(){

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int N;
  cin>>N;
  size_t weight[N][N];
  dwgraph<size_t> graph(N);
  std::vector< std::vector<size_t> > dist(N,std::vector<size_t>(N));
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      cin>>weight[i][j];
    }
  }
  stack<size_t> deletes;

  for(int i=0 ; i < N ; i++){
    size_t aux;
    cin>>aux;
    deletes.push(aux);
  }

  auto first1 = deletes.top();
  deletes.pop();
  std::cout << "first1 :"<<first1 << '\n';

  for(int k = 1 ; k < N ; k++){
    //meto k al grafo
    if(k==1){
      auto first2 = deletes.top();
      deletes.pop();
      for (size_t l = 0; l < 2; l++) {
        graph.connect(first1,first2,weight[first1][first2]);
        graph.connect(first2,first1,weight[first2][first1]);
      }
      for (size_t i = 0 ; i<2 ;i++){
        for(size_t j = 0 ; j<N ;j++){
          dist[i].push_back(0);
        }
      }

      for(int i = 0 ; i < N ; i++){
        for (const auto &elem : graph.get(i)){
          dist[i][j] = min( dist[i][j] , dist[i][elem.first]+dist[elem.first][j] );
        }
      }
    }

    for(int i = 0 ; i < N ; i++){
      for(int j = 0 ; j < N ;j++){

      }
    }


    for(int i = 0 ; i < N ; i++){
      for (const auto &elem : graph.get(i)){
        dist[i][j] = min( dist[i][j] , dist[i][elem.first]+dist[elem.first][j] );
      }
    }

  }

}
