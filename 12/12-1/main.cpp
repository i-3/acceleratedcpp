#include <iostream>
#include <cstring>

void strcpy_(char *arr, const char *cp)
{
    while (*cp != '\0')
        *arr++ = *cp++;
    *arr = *cp;
}
size_t strlen_(const char *p)
{
    size_t size = 0;
    while (*p++ != '\0')
        ++size;
    return size;
}

class Str
{
public:
    Str() {}
    Str(const char *cp) { strcpy_(arr, cp); }

    void operator=(const char *cp) { strcpy_(arr, cp); };
    char &operator[](size_t i) { return arr[i]; }
    const char &operator[](size_t i) const { return arr[i]; }
    size_t size() const { return strlen_(arr); }

private:
    char *arr;
};

int main()
{
    // Str s;
    // s = "hello";

    Str s = "hello!";

    std::cout << s[0] << "\n";
    std::cout << s.size() << "\n";

    return 0;
}
