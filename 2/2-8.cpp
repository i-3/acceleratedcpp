#include <iostream>
int main()
{
    int i = 1;
    int product = 1;
    while (i < 10)
    {
        product *= i;
        i += 1;
    }
    std::cout << product << std::endl;
    return 0;
}