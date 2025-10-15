#include <iostream>
#include "Str.hpp"

int main()
{
    Str s("hello");
    Str t = "hello";
    s = "hello";

    std::cout << t[0] << "\n";

    return 0;
}
