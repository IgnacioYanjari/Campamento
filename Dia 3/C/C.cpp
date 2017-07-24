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

int Knapsack_mod_Botttom(  std::vector< std::vector<int> > &memoized, std::map<int,std::vector<int>> list_types, int i , int budget){
  for (size_t i = 0; i < memoized.size(); i++) {
    for (size_t j = 0; j < memoized.at(0).size(); j++) {
        if( i == 0){
          int maximum=0;
            for( auto &model_price : list_types[i]){
              if ( model_price <= j) {
                maximum = std::max(maximum,model_price);
              }
            };
          memoized.at(i).at(j) = maximum;
        }
        else{
          int maximum = 0;
          for( auto &model_price : list_types[i]){
              if( j - model_price < 0){
                memoized.at(i).at(j) = -1e8+1;
              }
              else
                memoized.at(i).at(j) = memoized.at(i-1).at(j - model_price ) + model_price ;
          }
        }
    }
  }
  return memoized.at(i).at(budget);
}


int  Knapsack_mod( std::vector< std::vector<int> > &memoized, std::map<int,std::vector<int>> list_types, int i ,int budget){
  if(budget < 0  || i < 0){
    return -1e8+1;
  }
  if (memoized.at(i).at(budget) != 0){
    return memoized.at(i).at(budget);
  }
  else if( i == 0 ){
    int maximum=-1e8+1;
    if (list_types.find(i) != list_types.end()){
      for( const auto model_price : list_types[i]){
        if ( model_price <= budget)
          maximum = std::max(maximum,model_price);
      }
    }
    return memoized.at(i).at(budget) = maximum;
  }
  else{
    int maximum = -1e8+1;
    if (list_types.find(i) != list_types.end()){
      for( const auto model_price : list_types[i]){
          maximum = std::max( maximum , Knapsack_mod( memoized , list_types , i-1 ,budget - model_price ) + model_price );
      }
    }
    return memoized.at(i).at(budget) = maximum;
  }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto N = input_value<int >();
    while(N--){
      auto budget = input_value<int >();
      auto types = input_value<int >();
      std::vector< std::vector<int> > memoized(types , std::vector<int>(budget+1));
      std::map<int  ,std::vector<int > > list_types;
      for (int  i = 0; i < types; i++) {
        auto num_model = input_value<int>();
        for (int   j= 0;  j < num_model ; j++) {
          auto model = input_value<int>();
          list_types[i].push_back(model);
        }
      }
      auto result = Knapsack_mod( memoized , list_types, types-1, budget) ;
      if (result < 0)
        std::cout << "no solution" << '\n';
      else
        std::cout << result << '\n';
    }
}
