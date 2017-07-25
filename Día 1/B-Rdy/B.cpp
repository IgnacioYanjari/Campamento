#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::size_t;

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

template <typename T> T ipow(T base, size_t k) {
  T result = 1;
  while (k--) {
    result *= base;
  }
  return result;
}

int main() {
  auto n = input<unsigned long long>();
  auto x = input<unsigned long long>();
  auto k = input<unsigned long long>();

  auto exp_value = ipow(k, x);

  std::vector<unsigned long long> numbers(n);
  std::vector<unsigned long long> orA(n);
  std::vector<unsigned long long> orB(n);

  for (auto &elem : numbers)
    cin >> elem;

  for (size_t ix = 0; ix < n - 1; ++ix)
    orA.at(ix + 1) = orA.at(ix) | numbers.at(ix);

  for (size_t ix = n - 1; ix > 0; --ix)
    orB.at(ix - 1) = numbers.at(ix) | orB.at(ix);

  unsigned long long ans = 0;
  for (size_t ix = 0; ix < n; ++ix) {
    ans = std::max(ans, orA.at(ix) | numbers.at(ix) * exp_value | orB.at(ix));
  }

  cout << ans << '\n';

  return 0;
}
