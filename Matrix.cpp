#include <stdexcept>
#include <sstream>
#include "Matrix.h"

Matrix::Matrix(unsigned int a, unsigned int b, int content) : mSize1(a), mSize2(b),
                                                              mData(std::vector<std::vector<int>>()) {
    if (a == 0 || b == 0) {
        throw std::invalid_argument("Matrix size should be positive");
    }
    for (int i = 0; i < a; ++i) {
        mData.emplace_back();
        for (int j = 0; j < b; ++j) {
            mData[i].push_back(content);
        }
    }
}

Matrix::Matrix(int x) : Matrix(1, 1, x) {
}

template<typename Operation>
Matrix Matrix::constUnaryOperation(Operation operation) const {
    Matrix res = *this;
    for (auto &i : res.mData) {
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
    return constUnaryOperation([](int &x) { x = -x; });
}

Matrix Matrix::operator~() const {
    return constUnaryOperation([](int &x) { x = ~x; });
}

template<typename Operation>
Matrix &Matrix::changingBinaryOperation(const Matrix &other, Operation operation) {
    if (mSize1 != other.mSize1 || mSize2 != other.mSize2) {
        throw std::invalid_argument("Operations are forbidden for different-sized matrix");
    }
    for (int i = 0; i < mSize1; ++i) {
        for (int j = 0; j < mSize2; ++j) {
            operation(mData[i][j], other.mData[i][j]);
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
    for (auto &i : mData) {
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
    if (mSize2 != other.mSize1) {
        throw std::invalid_argument("Wrong matrix for multiplication");
    }
    Matrix res = Matrix(mSize1, other.mSize2);
    for (int i = 0; i < mSize1; ++i) {
        for (int j = 0; j < other.mSize2; ++j) {
            int x = 0;
            for (int k = 0; k < mSize2; ++k) {
                x += mData[i][k] * other.mData[k][j];
            }
            res.mData[i][j] = x;
        }
    }
    return *this = res;
}

Matrix &Matrix::operator++() {
    return *this += 1;
}

const Matrix Matrix::operator++(int) {
    Matrix res(*this);
    ++*this;
    return res;
}

Matrix &Matrix::operator--() {
    return *this -= 1;
}

const Matrix Matrix::operator--(int) {
    Matrix res(*this);
    --*this;
    return res;
}

Matrix::operator bool() const {
    for (auto &i : mData) {
        for (auto j : i) {
            if (j != 0) {
                return true;
            }
        }
    }
    return false;
}


bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.mSize1 != rhs.mSize1 || lhs.mSize2 != rhs.mSize2) {
        return false;
    }
    for (int i = 0; i < lhs.mSize1; ++i) {
        for (int j = 0; j < lhs.mSize2; ++j) {
            if (lhs.mData[i][j] != rhs.mData[i][j]) {
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
    for (auto &i : mData) {
        res << '[';
        for (auto j : i) {
            res << j << ' ';
        }
        res << "]\n";
    }
    //res << ']';
    return res.str();
}

Matrix::Row Matrix::operator[](unsigned int pos) {
    return Row(mData[pos]);
}

const Matrix::Row Matrix::operator[](unsigned int pos) const {
    return Row(mData[pos]);
}


Matrix::Row::Row(const std::vector<int> &vector): mData(vector) {
}

int &Matrix::Row::operator[](unsigned int pos) {
    return const_cast<int &>(mData[pos]);
}

int Matrix::Row::operator[](unsigned int pos) const {
    return mData[pos];
}

std::ostream &operator<<(std::ostream &s, Matrix const &matrix) {
    return s << std::string(matrix);
}
