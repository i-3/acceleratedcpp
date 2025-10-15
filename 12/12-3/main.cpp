#include <iostream>
#include <cstring>

class Str
{
public:
    void cp(const char *c)
    {
        arr = new char[0];
        int n = strlen(c);
        for (int i = 0; i < n; i++)
            arr[i] = c[i];
    };

    Str() {}
    Str(const char *c) { cp(c); }
    void operator=(const char *c) { cp(c); };
    char &operator[](size_t i) { return arr[i]; }
    const char &operator[](size_t i) const { return arr[i]; }
    size_t size() const { return strlen(arr); }
    char *c_str_() { return arr; };
    char *data_()
    {
        char *A;
        A = new char[0];
        for (int i = 0; arr[i] != '\0'; i++)
            A[i] = arr[i];
        return A;
    };
    void copy_(char *p, int n)
    {
        for (int i = 0; i <= n; i++)
            p[i] = arr[i];
    };
    int strcmp(const char *str)
    {
        int len = strlen(arr);
        int len2 = strlen(str);
        if (len < len2)
            return -1;
        if (len > len2)
            return 1;
        return 0;
    };

private:
    char *arr;
};

int main()
{
    Str s;
    s = "Hello";

    std::cout << s.strcmp("Hello!") << "\n";

    return 0;
}
