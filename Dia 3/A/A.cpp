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

void dp1(std::vector< std::vector<int> > &v , std::string f1 , std::string f2){

  int N = v.size();

   for (size_t i = 0; i < N; i++) {
     v.at(N-1).at(i) = 0;
     v.at(i).at(N-1) = 0;
     v.at(0).at(i) = 0;
     v.at(i).at(0) = 0;

  }

  for (size_t i = 1; i < N-1; i++) {
    for (size_t j = 1; j < N-1; j++) {
      if( f1[i-1] == f2[j-1]){
        //std::cout << " i :"<<i<<" j :"<<j << '\n';
        v.at(i).at(j) = 1 + v.at(i-1).at(j-1);
      }
      else
        v.at(i).at(j) = std::max( v.at(i-1).at(j) , v.at(i).at(j-1) );
    }
  }
}

int dp2(std::vector< std::vector<int> > &v, int i , int j , std::string f1 , std::string f2){
  if( j == -1 || i == -1)
    return 0;
  if( v.at(i).at(j) != 0 )
    return v.at(i).at(j);
  if( f2[j] == f1[i] ){
    v.at(i).at(j) = 1 + dp2(v,i-1,j-1,f1,f2);
    return v.at(i).at(j);
  }
  else{
    return v.at(i).at(j) = std::max( dp2(v,i-1,j,f1,f2) , dp2(v,i,j-1,f1,f2)  );
  }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    cin>>N;
    std::string f1;
    for(int i = 0 ; i < N ; i++){
      cin>>f1;
      std::string f2 = f1;
      int large =f1.size();
      std::reverse(f2.begin(),f2.end());
      std::vector< std::vector<int> > v1(large+2,std::vector<int>(large+2));
      dp2(v1,f1.size()-1,f1.size()-1,f1,f2);
      std::cout <<large - v1.at(large).at(large) << '\n';
    }

}
