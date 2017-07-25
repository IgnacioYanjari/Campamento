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
#define rep(i,n) for(int i=0;i<(int)n;++i)
#define invrep(i,n) for(int i=n-1;i>=0;--i)
typedef unsigned long long ull;
ull mod[] = {(int)1e9+7, (int)1e9+9};
//largo máximo que puede tener un string
int maxstrlen = 1e6;

class RH {
    static std::vector<ull> x[2];
    vector<ull> h[2];
    string str;
    int n;
    //private: usar el método público para obtener el hash
    ull hash(int a, int start, int len) {
        ull ans = 0, end = start + len;
        //descomentar si se consideran substrings cíclicos
        //if (end > n) {end -= n; ans = h[a][0]*x[a][n-start] %mod[a];}
        ans += h[a][start] - h[a][end]*x[a][len] %mod[a] + mod[a];
        return ans %mod[a];
    }

public: RH() {}
    //str: string del cual se producen substrings a hashear
    RH(const string &str) { // complejidad: O(n)
        this->str = str;
        n = str.size();
        if (x[0].empty()) rep(a, 2) {
            x[a].assign(maxstrlen+1, 1);
            rep(i, maxstrlen) x[a][i+1] = x[a][i]*127 %mod[a];
        }
        rep(a, 2) {
            h[a].assign(n+1, 0);
            invrep(i, n) h[a][i] = (h[a][i+1]*127 + str[i]) %mod[a];
        }
    }

    //obtiene el hash de un substring que comienza en el índice “start”
    //y tiene largo “len”.
    ull hash(int start, int len) { // complejidad: O(1)
        return hash(0, start, len) << 32 | hash(1, start, len);
    }

    //si se usan, insertar aquí los métodos opcionales 1 o 2.

};
//esta línea es importante para que el código compile
vector<ull> RH::x[2];

//comparar dos substrings
//     01234567890123

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string str;
  int n;
  std::cin >> str >> n;
  std::vector<int> pattern(n);

  for (auto &elem : pattern)
    std::cin >> elem;

  string letters[26];
  for( int i = 0 ; i < 26 ;i++ ){
    string aux= "";
    for( int j = 0 ; j < str.size(); j++ ){
      if(str[j] == (char)i+97) aux += "1";
      else aux += "0";
    }
    letters[i] = aux ;
  }

  // for (auto &elem : letters)
  //     std::cout << elem << '\n';

  std::map<int,int> subpattern;
  int cnt = 0 , k[pattern.size()];
  for( int i = 0 ; i < pattern.size() ; i++){
    auto b = subpattern.find(pattern[i]);
    if( b != subpattern.end() ){
      k[i] = b->second;
    }
    else {
      cnt++;
      k[i] = cnt;
      subpattern[pattern[i]] = cnt;
    }
  }

  //  std::cout << "subpattern" << '\n';
  //  for (auto &elem : subpattern){
  //    std::cout <<"first : " <<elem.first << '\n';
  //    std::cout <<"second : "<< elem.second << '\n';
  //  }
  //Hacer mapa de key :  int y par string

  std::map<int, string> hashed_patterns;
  // encontrar mayor en k
  for(int i= 1 ; i <= cnt ;i++){
    string aux="";
    for(const auto &elem : k){
      if( elem == i )  aux+= '1';
      else aux+='0';
    }
    //std::cout << i << " pattern : "<< aux << '\n';
    hashed_patterns[i] = string(aux);
  }
  //   std::cout << "hashed_patterns" << '\n';
  //   for (auto &elem : hashed_patterns){
  //     std::cout <<"second : " << elem.second << '\n';
  //     std::cout << "first : " << elem.first<< '\n';
  //  }
  int cnt2 = 0;
  for (int i = 0 ; i < str.size() - n + 1 ; i++){
    std::map<int,bool> check;
    //std::cout <<"patron "<< i << '\n';
    int cnt3=0;
    for(int k = 0 ; k < n ; k++){
      auto b = check.find(pattern[k]);
      if (b==check.end()){
      //  std::cout << pattern[k] << '\n';
        auto a = subpattern.find(pattern[k]);
        auto c = hashed_patterns.find(a->second);
         RH rh(letters[str[i+k]-97]);
         RH rh2(c->second);
        // std::cout<<"patron de "<< str[i+k] <<" : "<< letters[str[i+k]-97].substr(i,c->second.size())<< '\n';
        // std::cout << c->second << '\n';
        if ( rh.hash(i,c->second.size()) == rh2.hash(0,c->second.size())){
          //std::cout << "entra" << '\n';
          cnt3++;
        }
        // std::cout << "cnt3 : "<<cnt3 << '\n';
        // std::cout << "cnt : " <<cnt<< '\n';
        // std::cout << "check size : "<<check.size() << '\n';
        check[pattern[k]]=true;
        if( check.size()==cnt && cnt3 == cnt){
          //std::cout << "dsa" << '\n';
          cnt2++;
          cnt3=0;
        }
      }
    }
  }
  std::cout << cnt2<<"\n";
  // RH rh("hola hola chao");
  //
  // RH rh2("hola rh2");
  // if (rh.hash(0, 4) == rh2.hash(0, 4)) std::cout << "Yes" << '\n';
  // else std::cout << "No" << '\n';

}
