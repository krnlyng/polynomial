#include <iostream>
#include <vector>

#include "polynomial.h"

int main(int argc, char *argv[])
{
    polynomial<double> a, b;
    a.set(0, 1.f);
    a.set(2, 1.f);
    b.set(1, 2.f);
    b.set(4, 2.f);

    std::cout << a+b << std::endl;

    return 0;
}

