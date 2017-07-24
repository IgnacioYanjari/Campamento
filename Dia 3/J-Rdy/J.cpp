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

long long dp(std::vector< std::vector<long long> > &memoized , std::map< std::pair<long long , long long > ,bool > wolfs ){
  for (long long i = 1; i < memoized.size(); i++) {
    for (long long j = memoized.at(0).size()-2; j >= 0  ; j--) {
      if( wolfs.find( std::make_pair(i,j)) != wolfs.end() ){
        memoized.at(i).at(j) = 0;
      }
      else if ( i == 1  && j == memoized.at(0).size()-2) {
        memoized.at(i).at(j) = 1;
      }
      else{
        memoized.at(i).at(j) = memoized.at(i-1).at(j) + memoized.at(i).at(j+1); //+ memoized.at(i-1).at(j+1);
      }
    }
  }
  return memoized.at(memoized.size()-1).at(0);
}


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int cases=1;
    long long width,height;
    while(true){
    cin>>width>>height;
    if ( width == 0 && height == 0)
      break;
    std::map< std::pair<long long , long long>,bool> wolfs;
    height=height+1;
    width=width+1;
    std::vector<std::vector<long long>> memoized(height+1, std::vector<long long>(width+1));
    long long number_of_wolfs;
    cin>>number_of_wolfs;
    for (long long i = 0; i < number_of_wolfs; i++) {
      long long x,y;
      cin>>x>>y;
      wolfs[std::make_pair(height - y ,x)] = true;
    }
    cases++;
    auto result = dp(memoized,wolfs);
    if ( result == 0)
      std::cout << "There is no path." << '\n';
    else if ( result == 1 )
      std::cout << "There is one path from Little Red Riding Hood's house to her grandmother's house." << '\n';
    else
      std::cout << "There are "<< result << " paths from Little Red Riding Hood's house to her grandmother's house." << '\n';
    // for( auto &subarray : memoized){
    //   for (auto &elem : subarray) {
    //     std::cout<<"\t" << elem <<"\t";
    //   }
    //   std::cout << '\n';
    // }
  }

}
