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

class dwgraph{
  public:

  private:
};


int main(){

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int N;
  cin>>N;
  std::vector< std::vector<int> > matrix(N, std::vector<int>(N,0));
  int dist[N][N];
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      cin>>dist[i][j];
    }
  }

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix[i][j] = dist[i][j];
    }
  }

  std::cout << "\t Matrix :" << '\n';
  for(auto &subvector : matrix){
    for( auto &elem : subvector){
      std::cout<<"\t"<<elem<<" ";
    }
    std::cout << '\n';
  }

  std::vector<int> deletes(N);
  for(auto &elem : deletes)
    cin>>elem;
  std::cout << "\t Deletes : " << '\n';
  for(auto &elem : deletes)
    std::cout<<"\t"<< elem<<" ";
  std::cout<< '\n';
  for (size_t k = 0; k < N; k++) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N ; j++) {
        dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
      }
    }
  }
  std::cout << "Dist :" << '\n';
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      std::cout << dist[i][j]<<" ";
    }
    std::cout<< '\n';
  }

}
