#include <iostream>
// #include "Str.hpp"
#include "Vec.hpp"
#include "Vec.cpp"
#include <cstring>

int main()
{
    char arr[] = "Hello!";
    Vec<char> v;
    v.assign(arr);

    std::cout << v[5] << "\n";

    return 0;
}
