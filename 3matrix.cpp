#include <algorithm>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 private:
  std::vector<std::vector<T>> matrix_;

 public:
  Matrix() {
    std::vector<T> vec_build(M);
    matrix_.resize(N, vec_build);
  }

  Matrix(const std::vector<std::vector<T>>& vec_build) : matrix_(vec_build){};

  Matrix(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      matrix_.push_back(std::vector<T>());
      for (size_t j = 0; j < M; ++j) {
        matrix_[i].push_back(elem);
      }
    }
  };

  Matrix operator+(const Matrix& mat1) const {
    Matrix ret(*this);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        ret.matrix_[i][j] += mat1.matrix_[i][j];
      }
    }
    return ret;
  }

  Matrix& operator+=(const Matrix& mat1) {
    *this = *this + mat1;
    return *this;
  }

  Matrix operator-(const Matrix& mat1) const {
    Matrix ret(*this);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        ret.matrix_[i][j] -= mat1.matrix_[i][j];
      }
    }
    return ret;
  }

  Matrix& operator-=(const Matrix& mat1) {
    *this = *this - mat1;
    return *this;
  }

  Matrix operator*(const T& elem) const {
    Matrix ret(*this);
    return ret *= elem;
  }

  Matrix& operator*=(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] *= elem;
      }
    }
    return *this;
  }

  T& operator()(size_t iii, size_t jjj) { return matrix_[iii][jjj]; }

  T operator()(size_t iii, size_t jjj) const { return matrix_[iii][jjj]; }

  bool operator==(const Matrix& mat1) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (matrix_[i][j] != mat1.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix<M, N, T> Transposed() const {
    Matrix<M, N, T> ret;
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        ret(i, j) = matrix_[j][i];
      }
    }
    return ret;
  }
};

template <size_t N, size_t M, size_t K, typename T>
Matrix<N, K, T> operator*(const Matrix<N, M, T>& mat1,
                          const Matrix<M, K, T>& mat2) {
  Matrix<N, K, T> ret;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      for (size_t k = 0; k < M; ++k) {
        ret(i, j) += mat1(i, k) * mat2(k, j);
      }
    }
  }
  return ret;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const T& elem, const Matrix<N, M, T>& mat1) {
  Matrix ret(mat1);
  return ret *= elem;
}

template <size_t N, typename T>
class Matrix<N, N, T> {
 private:
  std::vector<std::vector<T>> matrix_;

 public:
  Matrix() {
    std::vector<T> vec_build(N);
    matrix_.resize(N, vec_build);
  }

  Matrix(const std::vector<std::vector<T>>& vec_build) : matrix_(vec_build){};

  Matrix(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      matrix_.push_back(std::vector<T>());
      for (size_t j = 0; j < N; ++j) {
        matrix_[i].push_back(elem);
      }
    }
  };

  Matrix operator+(const Matrix& mat1) const {
    Matrix ret(*this);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        ret.matrix_[i][j] += mat1.matrix_[i][j];
      }
    }
    return ret;
  }

  Matrix& operator+=(const Matrix& mat1) {
    *this = *this + mat1;
    return *this;
  }

  Matrix operator-(const Matrix& mat1) const {
    Matrix ret(*this);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        ret.matrix_[i][j] -= mat1.matrix_[i][j];
      }
    }
    return ret;
  }

  Matrix& operator-=(const Matrix& mat1) {
    *this = *this - mat1;
    return *this;
  }

  Matrix operator*(const T& elem) const {
    Matrix ret(*this);
    return ret *= elem;
  }

  Matrix& operator*=(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        matrix_[i][j] *= elem;
      }
    }
    return *this;
  }

  T& operator()(size_t iii, size_t jjj) { return matrix_[iii][jjj]; }

  T operator()(size_t iii, size_t jjj) const { return matrix_[iii][jjj]; }

  bool operator==(const Matrix& mat1) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        if (matrix_[i][j] != mat1.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix<N, N, T> Transposed() const {
    Matrix<N, N, T> ret;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        ret.matrix_[i][j] = matrix_[j][i];
      }
    }
    return ret;
  }

  T Trace() const {
    T ret = T();
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        if (i == j) {
          ret += matrix_[i][j];
        }
      }
    }
    return ret;
  }
};