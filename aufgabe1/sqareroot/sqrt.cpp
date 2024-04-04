// should implement the function newton_sqrt

#include <iostream>
#include <cmath>
#include <cassert>

// function to calculate square root using newton's method
double newton_sqrt(double x)
{
    assert(x >= 0);
    double guess = x;
    double root = 0;
    while (true)
    {
        root = (guess + x / guess) / 2;
        if (std::abs(root - guess) < 0.0001)
        {
            break;
        }
        guess = root;
    }
    std::cout << "Square root of " << x << " is " << root << std::endl;
    return root;
}

// main function
int main()
{
    while (true) {
        // read input, exit if input is "exit", else calculate square root
        double x;
        std::cout << "Enter a number to calculate square root: ";
        std::cin >> x;
        if (std::cin.fail())
        {
            return 0;
        }
        else if (x < 0)
        {
            std::cout << "Square root of negative number is not possible" << std::endl;
        }
        else
        {
            newton_sqrt(x);
        }
    }
}

