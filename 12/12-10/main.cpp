#include <iostream>
#include "Str.hpp"

int main()
{

    // char str[] = {'H', 'e', 'l', 'l', 'o', '!'};
    // Str s(std::begin(str), std::end(str));
    char const *str = "Hello!";
    Str s(str, str + strlen(str));

    std::cout << s << "\n";

    return 0;
}
