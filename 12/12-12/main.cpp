#include <iostream>
// #include "Str.hpp"
#include "Vec.hpp"
#include "Vec.cpp"
#include <cstring>

class Str
{
    friend std::istream &operator>>(std::istream &, Str &);

public:
    Str &operator+=(const Str &s)
    {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }
    typedef Vec<char>::size_type size_type;
    Str() {}
    Str(size_type n, char c) : data(n, c) {}
    Str(const char *cp)
    {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }
    template <class In>
    Str(In b, In e)
    {
        // std::copy(b, e, std::back_inserter(data));
        data = Vec(b, e);
    }
    char &operator[](size_type i) { return data[i]; }
    const char &operator[](size_type i) const { return data[i]; }
    size_type size() const { return data.size(); }
    char *begin() { return data.begin(); }

    char *insert(char *pos, char *in)
    {
        data.insert(pos, in);
        return pos;
    };

private:
    Vec<char> data;
};

std::ostream &operator<<(std::ostream &os, const Str &s)
{
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}
std::istream &operator>>(std::istream &is, Str &s)
{
    s.data.clear_();
    char c;
    while (is.get(c) && isspace(c))
        ;

    if (is)
    {
        do
            s.data.push_back(c);
        while (is.get(c) && !isspace(c));

        if (is)
            is.unget();
    }
    return is;
}
Str operator+(const Str &s, const Str &t)
{
    Str r = s;
    r += t;
    return r;
}

int main()
{
    Str s("Hello!");
    char *pos = s.begin() + 5;
    char in[] = ", world";
    s.insert(pos, in);

    std::cout << s << "\n";

    return 0;
}
