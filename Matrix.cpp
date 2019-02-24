#include <stdexcept>
#include <sstream>
#include "Matrix.h"

Matrix::Matrix(unsigned int a, unsigned int b, int content) : size1(a), size2(b),
                                                              data(std::vector<std::vector<int>>()) {
    if (a == 0 || b == 0) {
        throw std::invalid_argument("Matrix size should be positive");
    }
    for (int i = 0; i < a; ++i) {
        data.emplace_back();
        for (int j = 0; j < b; ++j) {
            data[i].push_back(content);
        }
    }
}

Matrix::Matrix(int x) : Matrix(1, 1, x) {
}

template<typename Operation>
Matrix Matrix::constUnaryOperation(Operation operation) const {
    Matrix res = *this;
    for (auto &i : res.data) {
        for (auto &j : i) {
            operation(j);
        }
    }
    return res;
}

Matrix Matrix::operator+() const {
    return *this;
}

Matrix Matrix::operator-() const {
    return constUnaryOperation([](int &x) { return -x; });
}

Matrix Matrix::operator~() const {
    return constUnaryOperation([](int &x) { return ~x; });
}

template<typename Operation>
Matrix &Matrix::changingBinaryOperation(const Matrix &other, Operation operation) {
    if (size1 != other.size1 || size2 != other.size2) {
        throw std::invalid_argument("Operations are forbidden for different-sized matrix");
    }
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            operation(data[i][j], other.data[i][j]);
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    return changingBinaryOperation(other, [](int &a, int b) { a += b; });
}

Matrix &Matrix::operator-=(const Matrix &other) {
    return changingBinaryOperation(other, [](int &a, int b) { a -= b; });
}

Matrix &Matrix::operator&=(const Matrix &other) {
    return changingBinaryOperation(other, [](int &a, int b) { a &= b; });
}

Matrix &Matrix::operator|=(const Matrix &other) {
    return changingBinaryOperation(other, [](int &a, int b) { a |= b; });
}

Matrix &Matrix::operator^=(const Matrix &other) {
    return changingBinaryOperation(other, [](int &a, int b) { a ^= b; });
}

template<typename Operation, typename ArgType>
Matrix &Matrix::changingMemberOperation(ArgType argument, Operation operation) {
    for (auto &i : data) {
        for (auto &j : i) {
            operation(j, argument);
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a += b; });
}

Matrix &Matrix::operator-=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a -= b; });
}

Matrix &Matrix::operator&=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a &= b; });
}

Matrix &Matrix::operator|=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a |= b; });
}

Matrix &Matrix::operator^=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a ^= b; });
}

Matrix &Matrix::operator*=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a *= b; });
}

Matrix &Matrix::operator/=(int x) {
    return changingMemberOperation(x, [](int &a, int b) { a /= b; });
}

Matrix &Matrix::operator<<=(unsigned int x) {
    return changingMemberOperation(x, [](int &a, unsigned int b) { a <<= b; });
}

Matrix &Matrix::operator>>=(unsigned int x) {
    return changingMemberOperation(x, [](int &a, unsigned int b) { a >>= b; });
}

Matrix &Matrix::operator*=(const Matrix &other) {
    if (size2 != other.size1) {
        throw std::invalid_argument("Wrong matrix for multiplication");
    }
    Matrix res = Matrix(size1, other.size2);
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < other.size2; ++j) {
            int x = 0;
            for (int k = 0; k < size2; ++k) {
                x += data[i][k] * other.data[k][j];
            }
            res.data[i][j] = x;
        }
    }
    return *this = res;
}

Matrix &Matrix::operator++() {
    return *this += 1;
}

const Matrix Matrix::operator++(int) {
    Matrix res = *this;
    return ++res;
}

Matrix &Matrix::operator--() {
    return *this -= 1;
}

const Matrix Matrix::operator--(int) {
    Matrix res = *this;
    return --res;
}

Matrix::operator bool() const {
    for (auto &i : data) {
        for (auto j : i) {
            if (j != 0) {
                return true;
            }
        }
    }
    return false;
}


std::vector<int> &Matrix::operator[](unsigned int pos) {
    return data[pos];
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.size1 != rhs.size1 || lhs.size2 != rhs.size2) {
        return false;
    }
    for (int i = 0; i < lhs.size1; ++i) {
        for (int j = 0; j < lhs.size2; ++j) {
            if (lhs.data[i][j] != rhs.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {
    return !(lhs == rhs);
}

Matrix operator+(Matrix lhs, const Matrix &rhs) {
    return lhs += rhs;
}

Matrix operator-(Matrix lhs, const Matrix &rhs) {
    return lhs -= rhs;
}

Matrix operator*(Matrix lhs, const Matrix &rhs) {
    return lhs *= rhs;
}

Matrix operator&(Matrix lhs, const Matrix &rhs) {
    return lhs &= rhs;
}

Matrix operator|(Matrix lhs, const Matrix &rhs) {
    return lhs |= rhs;
}

Matrix operator^(Matrix lhs, const Matrix &rhs) {
    return lhs ^= rhs;
}

Matrix operator+(Matrix lhs, int rhs) {
    return lhs += rhs;
}

Matrix operator-(Matrix lhs, int rhs) {
    return lhs -= rhs;
}

Matrix operator*(Matrix lhs, int rhs) {
    return lhs *= rhs;
}

Matrix operator/(Matrix lhs, int rhs) {
    return lhs /= rhs;
}

Matrix operator&(Matrix lhs, int rhs) {
    return lhs &= rhs;
}

Matrix operator|(Matrix lhs, int rhs) {
    return lhs |= rhs;
}

Matrix operator^(Matrix lhs, int rhs) {
    return lhs ^= rhs;
}

Matrix operator>>(Matrix lhs, unsigned int rhs) {
    return lhs >>= rhs;
}

Matrix operator<<(Matrix lhs, unsigned int rhs) {
    return lhs <<= rhs;
}

Matrix::operator std::string() const {
    std::stringstream res;
    //res << "[\n";
    for (auto &i : data) {
        res << '[';
        for (auto j : i) {
            res << j << ' ';
        }
        res << "]\n";
    }
    //res << ']';
    return res.str();
}
