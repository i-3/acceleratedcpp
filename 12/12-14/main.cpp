#include <iostream>
// #include "Str.hpp"
#include "Vec.hpp"
#include "Vec.cpp"
#include <cstring>

int main()
{
    char const *str = "Hello!";

    Vec<char> v(str, str + strlen(str));

    std::cout << v[5] << "\n";

    return 0;
}
