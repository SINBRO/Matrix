#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H


#include <vector>

class Matrix {
public:
    explicit Matrix(unsigned int a = 1, unsigned int b = 1, int content = 0);

    explicit Matrix(int x);

    Matrix(const Matrix &other) = default;

    Matrix &operator=(const Matrix &other) = default;

    Matrix operator+() const;

    Matrix operator-() const;

    Matrix operator~() const;

    Matrix &operator+=(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator&=(const Matrix &other);

    Matrix &operator|=(const Matrix &other);

    Matrix &operator^=(const Matrix &other);

    Matrix &operator+=(int x);

    Matrix &operator-=(int x);

    Matrix &operator&=(int x);

    Matrix &operator|=(int x);

    Matrix &operator^=(int x);

    Matrix &operator*=(int x);

    Matrix &operator/=(int x);

    Matrix &operator<<=(unsigned int x);

    Matrix &operator>>=(unsigned int x);

    Matrix &operator*=(const Matrix &other);

    Matrix &operator++();

    const Matrix operator++(int);

    Matrix &operator--();

    const Matrix operator--(int);

    operator bool() const;

    operator std::string() const;

    class Row {
    public:
        explicit Row(const std::vector<int> &vector);

        int operator[](unsigned int pos) const;

        int &operator[](unsigned int pos);

    private:
        std::vector<int> const &mData;
    };

    Row operator[](unsigned int pos);

    Row const operator[](unsigned int pos) const;

    friend bool operator==(const Matrix &lhs, const Matrix &rhs);

private:
    unsigned int mSize1, mSize2;
    std::vector<std::vector<int>> mData;

    template<typename Operation>
    Matrix constUnaryOperation(Operation operation) const;

    template<typename Operation>
    Matrix &changingBinaryOperation(const Matrix &other, Operation operation);

    template<typename Operation, typename ArgType>
    Matrix &changingMemberOperation(ArgType argument, Operation operation);
};


bool operator!=(const Matrix &lhs, const Matrix &rhs);

Matrix operator+(Matrix lhs, const Matrix &rhs);

Matrix operator-(Matrix lhs, const Matrix &rhs);

Matrix operator*(Matrix lhs, const Matrix &rhs);

Matrix operator&(Matrix lhs, const Matrix &rhs);

Matrix operator|(Matrix lhs, const Matrix &rhs);

Matrix operator^(Matrix lhs, const Matrix &rhs);

Matrix operator+(Matrix lhs, int rhs);

Matrix operator-(Matrix lhs, int rhs);

Matrix operator*(Matrix lhs, int rhs);

Matrix operator/(Matrix lhs, int rhs);

Matrix operator&(Matrix lhs, int rhs);

Matrix operator|(Matrix lhs, int rhs);

Matrix operator^(Matrix lhs, int rhs);

Matrix operator>>(Matrix lhs, unsigned int rhs);

Matrix operator<<(Matrix lhs, unsigned int rhs);

std::ostream &operator<<(std::ostream &s, Matrix const &matrix);


#endif //UNTITLED1_MATRIX_H
