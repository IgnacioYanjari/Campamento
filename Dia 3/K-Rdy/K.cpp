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
template <class T>
T powi( size_t exponent , T  base ){
  T pot = 1;
  while(exponent--){
    pot *=base;
  }
  return pot;
}
template <class T>
T fact( T i){
  T prod = i;
  while(--i)
      prod *= i;
  return prod;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s1,s2;
    cin>>s1>>s2;

    long long Plus_s1=0,Plus_s2=0;
    long long Substract_s1=0,Substract_s2=0;
    long long questions = 0;

    for (size_t i = 0; i < s1.size(); i++) {
      if( s1[i] == '+')
        Plus_s1++;
      else
        Substract_s1++;
    }

    for (size_t i = 0; i < s1.size(); i++) {
      if( s2[i] == '+')
        Plus_s2++;
      else if (s2[i] == '-')
        Substract_s2++;
      else
        questions++;
    }
    // std::cout << "Plus_s1 : "<<Plus_s1 <<" Substract_s1 :"<<Substract_s1 << '\n';
    // std::cout << "Plus_s2 : "<<Plus_s2 <<" Substract_s2 :"<<Substract_s2 << '\n';
    long long sum1 = Plus_s1 - Substract_s1;
    long long sum2 = Plus_s2 - Substract_s2;
    std::vector<size_t> factor(11,1);
    for (size_t i = 2; i < factor.size(); i++) {
      //std::cout << " i + 1 : "<<i+1 <<"    : "<< factor.at(i-1)<<'\n';
        factor.at(i) = (i) * factor.at(i-1);
    }
    // for(auto elem : factor)
    //   std::cout << elem << " ";
    // std::cout  << '\n';
    //std::cout << "sum2 :"<<sum2<<" sum1 :"<<sum1<<" questions :"<<questions << '\n';
    //std::cout << " Cantidad de + : "<< << '\n';
    if (questions == 0){
      if ( sum1 == sum2)
        std::cout << std::fixed<<std::setprecision(10)<<float(1) << '\n';
      else
        std::cout << std::fixed<<std::setprecision(10)<<float(0) << '\n';
    }
    else{
      // std::cout << Plus_s1 - Plus_s2 << '\n';
      // std::cout << "sum1 : "<<sum1 <<" sum2 : "<< sum2 - questions <<" " <<sum2 + questions<< '\n';
      if( sum1 >= sum2 - questions && sum1 <= sum2 + questions ){
        long long k1 = Plus_s1 - Plus_s2;
        //std::cout << k1 - questions << '\n';
        //long long k2 = Substract_s1 - Substract_s2;
        std::cout << std::fixed <<std::setprecision(10);
        std::cout << ( factor.at( questions ) / ( factor.at(k1) * factor.at( questions - k1 ) ) ) * powi(questions,0.5)  << '\n';

      }
      else
        std::cout << std::fixed<<std::setprecision(10)<<float(0) << '\n';
    }
    // ( q! / (k! * ( k - q)! ) ) * p^k * (1-p)^(q-k);
}
