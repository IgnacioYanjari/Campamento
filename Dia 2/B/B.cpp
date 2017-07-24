#include <cstddef> // size_t
#include <iostream>
#include <utility> // pair
#include <vector>  // vector

using std::cin;
using std::cout;
using std::size_t;

template <class Function> void repeat(std::size_t n, Function f) {
  while (n--)
    f();
}

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto n = input<size_t>();
  auto m = input<size_t>();

  repeat(m, [&] {

  });

  return 0;
}
