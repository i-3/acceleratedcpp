#include <iostream>
#include <cstring>
#include <iterator>

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

    Str() { *arr = '\0'; }
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
    bool operator==(const char *str) { return strlen(arr) == strlen(str); };
    bool operator!=(const char *str) { return strlen(arr) != strlen(str); };
    char *operator+(const char *str)
    {
        int len = strlen(arr);
        int i = 0;
        while (*(str + i) != '\0')
        {
            *(arr + len + i) = *(str + i);
            ++i;
        }
        return arr;
    };
    operator bool() { return strlen(arr); };

    struct Iter
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char *;
        using reference = char &;
        Iter(pointer ptr) : ptr_(ptr) {}
        reference operator*() const { return *ptr_; }
        Iter &operator++()
        {
            ptr_++;
            return *this;
        }
        friend bool operator!=(const Iter &a, const Iter &b) { return a.ptr_ != b.ptr_; }

    private:
        pointer ptr_;
    };
    Iter begin() { return Iter(&arr[0]); }
    Iter end() { return Iter(&arr[strlen(arr)]); }

    std::istream &getline(std::istream &is)
    {
        typedef std::istream_iterator<char> ii;
        copy(ii(is), ii(), arr);
        return is;
    };
    friend std::ostream &operator<<(std::ostream &os, Str arr)
    {
        int i = 0;
        while (arr[i] != '\0')
        {
            os << arr[i];
            ++i;
        }
        std::cout << "\n";
        return os;
    }

private:
    char *arr;
};

int main()
{
    // Str s;
    // s.getline(std::cin);
    // int i = 0;
    // while (s[i] != '\0')
    //     std::cout << s[i++];
    // std::cout << "\n";

    Str s = "Hello!";
    std::cout << s;

    return 0;
}
