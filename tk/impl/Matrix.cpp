#include "Matrix.h"

#include <iostream>
#include <cstdlib>
#include <sstream>

void testMatricies()
{
    Matrix<int, 5, 5> m;
    m.toIdentity();

    Matrix<int, 5, 5> identity_5x5
    {
        1, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 0, 1
    };

    if (m != identity_5x5)
    {
        std::cout << "Failed identity matrix init." << std::endl;
        std::cout << m << " != " << identity_5x5 << std::endl;
        std::exit(1);
    }

    if (m * m != m)
    {
        std::cout << "Failed 5x5 matrix multiplication (identity)." << std::endl;
        std::exit(1);
    }

    Matrix<int, 3, 4> m2
    ({
        1, 2, 3,
        5, 6, 7,
        9, 0, 1,
        -3, -4, -5
    });

    std::stringstream ss;
    ss << m2;

    std::stringstream expected;
    expected << "[" << std::endl;
    expected << "1  2  3" << std::endl;
    expected << "5  6  7" << std::endl;
    expected << "9  0  1" << std::endl;
    expected << "-3 -4 -5" << std::endl;
    expected << "]";

    if (ss.str() != expected.str())
    {
        std::cout << "Matrix stringify test failed:" << std::endl;
        std::cout << ss.str() << std::endl;
        std::cout << " != " << std::endl;
        std::cout << expected.str() << std::endl;
        std::exit(1);
    }

    m.fill([](unsigned int x, unsigned int y) -> int
    {
        if (x < y)
        {
            return 0;
        }

        return x + y + 1;
    });

    Matrix<double, 5, 5> copy1 {};
    copy1.fill([&m](auto x, auto y) { return m.getAt(x, y); });

    Matrix<double, 5, 5> copy2 {copy1};

    copy1.invert();
    Matrix<double, 5, 5> timesInverse { copy1 * copy2 };
    Matrix<int, 5, 5> rounded {};

    rounded.fill([&timesInverse](unsigned int x, unsigned int y)
    {
        return static_cast<int>(timesInverse.getAt(x, y));
    });

    if (rounded != identity_5x5)
    {
        std::cout << "Matrix multiply by inverse test failed:" << std::endl;
        std::cout << copy1 << std::endl;
        std::cout << " * " << std::endl;
        std::cout << copy2 << std::endl;
        std::cout << " == " << rounded << std::endl;
        std::cout << "is not the identity matrix.";
        std::exit(1);
    }
}

