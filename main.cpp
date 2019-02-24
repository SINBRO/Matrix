#include <iostream>
#include "Matrix.h"

void println(Matrix matrix, std::string message = "") {
    std::cout << (message == "" ? "" : message + ":\n") << static_cast<std::string>(matrix) << '\n';
}

int main() {
    Matrix m(2, 3, 1);
    println(m, "m");

    m[1][2] = 2;
    println(m, "Changing elements");

    m <<= 2;
    println(m, "Int shift");

    Matrix m1(2, 3, 0);
    m1[1][1] = 100;
    m1[0][2] = -10;

    m += m1;
    println(m, "Matrix addition");


    Matrix m2(3, 1, 1);
    m2[1][0] = 2;
    m2[2][0] = 3;

    println(m, "m");
    println(m2, "m2");

    m *= m2;

    println(m, "m *= m2");
}