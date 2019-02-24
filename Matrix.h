#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H


#include <vector>

class Matrix {
public:
    explicit Matrix(unsigned int a = 1, unsigned int b = 1, int content = 0);

    explicit Matrix(int x);

    Matrix(const Matrix& other) = default;

    Matrix& operator=(const Matrix& other) = default;

    Matrix operator+() const;

    Matrix operator-() const;

    Matrix operator~() const;

    Matrix& operator+=(const Matrix& other);

    Matrix& operator-=(const Matrix& other);

    Matrix& operator&=(const Matrix& other);

    Matrix& operator|=(const Matrix& other);

    Matrix& operator^=(const Matrix& other);

    Matrix& operator+=(int x);

    Matrix& operator-=(int x);

    Matrix& operator&=(int x);

    Matrix& operator|=(int x);

    Matrix& operator^=(int x);

    Matrix& operator*=(int x);

    Matrix& operator/=(int x);

    Matrix& operator<<=(unsigned int x);

    Matrix& operator>>=(unsigned int x);

    Matrix& operator*=(const Matrix& other);

    Matrix &operator++();

    const Matrix operator++(int);

    Matrix &operator--();

    const Matrix operator--(int);

    operator bool() const;

    operator std::string() const;

    std::vector<int>& operator[](unsigned int pos);

    friend bool operator==(const Matrix& lhs, const Matrix& rhs);

    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

    friend Matrix operator+(Matrix lhs, const Matrix &rhs);

    friend Matrix operator-(Matrix lhs, const Matrix& rhs);

    friend Matrix operator*(Matrix lhs, const Matrix& rhs);

    friend Matrix operator&(Matrix lhs, const Matrix& rhs);

    friend Matrix operator|(Matrix lhs, const Matrix& rhs);

    friend Matrix operator^(Matrix lhs, const Matrix& rhs);

    friend Matrix operator+(Matrix lhs, int rhs);

    friend Matrix operator-(Matrix lhs, int rhs);

    friend Matrix operator*(Matrix lhs, int rhs);

    friend Matrix operator/(Matrix lhs, int rhs);

    friend Matrix operator&(Matrix lhs, int rhs);

    friend Matrix operator|(Matrix lhs, int rhs);

    friend Matrix operator^(Matrix lhs, int rhs);

    friend Matrix operator>>(Matrix lhs, unsigned int rhs);

    friend Matrix operator<<(Matrix lhs, unsigned int rhs);

private:
    unsigned int size1, size2;
    std::vector<std::vector<int>> data;

    template<typename Operation>
    Matrix constUnaryOperation(Operation operation) const;

    template <typename Operation>
    Matrix& changingBinaryOperation(const Matrix &other, Operation operation);

    template <typename Operation, typename ArgType>
    Matrix& changingMemberOperation(ArgType argument, Operation operation);
};


#endif //UNTITLED1_MATRIX_H
