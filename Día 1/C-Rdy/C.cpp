#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
// gmt mylam 9/12 Diagrama electrico
using std::cin;
using std::cout;
using std::size_t;

template <typename T> class matrix {
public:
  using bounds_type = std::pair<size_t, size_t>;
  using row_iterator = typename std::vector<T>::iterator;
  using const_row_iterator = typename std::vector<T>::const_iterator;

public:
  matrix() = default;

  matrix(bounds_type bounds, const T &value = T())
      : nrows{bounds.first}, ncols{bounds.second}, data(nrows * ncols, value) {}

  void assign(bounds_type bounds, const T &value) {
    nrows = bounds.first;
    ncols = bounds.second;
    data.assign(nrows * ncols, value);
  }

  void resize(bounds_type bounds) {
    nrows = bounds.first;
    ncols = bounds.second;
    data.resize(nrows * ncols);
  }

  size_t num_rows() const { return nrows; }
  size_t num_cols() const { return ncols; }

  row_iterator operator[](size_t row_idx) {
    return data.begin() + row_idx * ncols;
  }

  const_row_iterator operator[](size_t row_idx) const {
    return data.begin() + row_idx * ncols;
  }

private:
  size_t nrows{};
  size_t ncols{};
  std::vector<T> data;
};

template <class T> T input(std::istream &input = std::cin) {
  T value;
  input >> value;
  return value;
}

template <typename T>
T sum_rectangules(matrix<T> &sumMatrix, std::pair<T, T> i, std::pair<T, T> j) {
  int sum;
  T num1 = sumMatrix[i.first - 1][j.second];
  T num2 = sumMatrix[j.first][i.second - 1];
  T num3 = sumMatrix[i.first - 1][i.second - 1];

  sum = sumMatrix[j.first][j.second] - (num1 + num2) + num3;
  return sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto n = input<size_t>();

  matrix<int> mat({n, n});
  matrix<int> sumMatrix({n + 1, n + 1});

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mat[i][j] = input<int>();
    }
  }

  for (int ix = 1; ix <= n; ix++) {
    for (int iy = 1; iy <= n; iy++) {
      sumMatrix[ix][iy] = sumMatrix[ix - 1][iy] + sumMatrix[ix][iy - 1] -
                          sumMatrix[ix - 1][iy - 1] + mat[ix - 1][iy - 1];
    }
  }

  int aux = -99999999;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = i; k <= n; ++k)
        for (int l = j; l <= n; ++l)
          aux = std::max(aux, sum_rectangules(sumMatrix, {i, j}, {k, l}));

  cout << aux << '\n';

  return 0;
}
