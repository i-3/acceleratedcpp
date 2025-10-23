#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Vec.hpp"
#include "Vec.cpp"
#include <cstring>

class Core
{
    friend class Student_info;

public:
    Core() : midterm(0), final(0) {}
    Core(std::istream &is) { read(is); }
    virtual ~Core() {}

    std::string name() const;
    virtual std::istream &read(std::istream &);
    virtual double grade() const;

protected:
    virtual Core *clone() const { return new Core(*this); }
    std::istream &read_common(std::istream &);
    double midterm, final;
    std::vector<double> homework;

private:
    std::string n;
};
std::string Core::name() const
{
    return n;
}
std::istream &Core::read_common(std::istream &in)
{
    in >> n >> midterm >> final;
    return in;
}
std::istream &read_hw(std::istream &in, std::vector<double> &hw)
{
    if (in)
    {
        hw.clear();
        double x;
        while (in >> x)
            hw.push_back(x);
        in.clear();
    }
    return in;
}
std::istream &Core::read(std::istream &in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}
double Core::grade() const
{
    if (homework.size() == 0)
        throw std::domain_error("student has done no homework");
    typedef std::vector<double>::size_type vec_sz;
    vec_sz size = homework.size();
    std::vector<double> hw = homework;
    std::sort(hw.begin(), hw.end());
    vec_sz mid = size / 2;
    double median =
        size % 2 == 0 ? (hw[mid] + hw[mid - 1]) / 2 : hw[mid];

    return 0.2 * midterm + 0.4 * final + 0.4 * median;
}

class Grad : public Core
{
public:
    Grad() : thesis(0) {}
    Grad(std::istream &is) { read(is); }

    std::istream &read(std::istream &);
    double grade() const;

protected:
    Grad *clone() const { return new Grad(*this); }

private:
    double thesis;
};
std::istream &Grad::read(std::istream &in)
{
    Core::read_common(in);
    in >> Grad::thesis;
    read_hw(in, Core::homework);
    return in;
}
double Grad::grade() const
{
    return std::min(Core::grade(), thesis);
}

template <class T>
T *clone(const T *tp)
{
    return tp->clone();
}
template <> //************************ template specialization
Vec<char> *clone(const Vec<char> *vp)
{
    return new Vec<char>(*vp);
}

template <class T>
class Ptr
{
public:
    // void make_unique()
    // {
    //     if (*refptr != 1)
    //     {
    //         --*refptr;
    //         refptr = new size_t(1);
    //         p = p ? clone(p) : 0;
    //     }
    // }

    Ptr() : p(0), refptr(new std::size_t(1)) {}
    Ptr(T *t) : p(t), refptr(new std::size_t(1)) {}
    Ptr(const Ptr &h) : p(h.p), refptr(h.refptr) { ++*refptr; }

    Ptr &operator=(const Ptr &);
    ~Ptr();
    operator bool() const { return p; }
    T &operator*() const
    {
        if (p)
            return *p;
        throw std::runtime_error("unbound Ptr");
    }
    T *operator->() const
    {
        if (p)
            return p;
        throw std::runtime_error("unbound Ptr");
    }

private:
    T *p;
    std::size_t *refptr;
};
template <class T>
Ptr<T> &Ptr<T>::operator=(const Ptr &rhs)
{
    ++*rhs.refptr;
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}
template <class T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}
bool compare_Core_ptrs(const Ptr<Core> p1, const Ptr<Core> p2)
{
    return p1->grade() < p2->grade();
}

// Does this version work?
class Str
{
    friend std::istream &operator>>(std::istream &, Str &);

public:
    Str &operator+=(const Str &s)
    {
        // data.make_unique();
        std::copy(s.data->begin(), s.data->end(),
                  std::back_inserter(*data));
        return *this;
    }
    typedef Vec<char>::size_type size_type;
    Str() : data(new Vec<char>) {}
    Str(const char *cp) : data(new Vec<char>)
    {
        std::copy(cp, cp + std::strlen(cp),
                  std::back_inserter(*data));
    }
    Str(size_type n, char c) : data(new Vec<char>(n, c)) {}
    template <class In>
    Str(In i, In j) : data(new Vec<char>)
    {
        std::copy(i, j, std::back_inserter(*data));
    }
    char &operator[](size_type i)
    {
        // data.make_unique();
        return (*data)[i];
    }
    const char &operator[](size_type i) const { return (*data)[i]; }
    size_type size() const { return data->size(); }

private:
    Ptr<Vec<char>> data;
};
std::ostream &operator<<(std::ostream &os, const Str &s)
{
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}
Str operator+(const Str &s, const Str &t)
{
    Str r = s;
    r += t;
    return r;
}

Vec<Str> split(const std::string &s)
{
    Vec<Str> ret;
    typedef std::string::size_type string_size;
    string_size i = 0;

    while (i != s.size())
    {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j)
        {
            ret.push_back(Str(s.substr(i, j - i).c_str()));
            i = j;
        }
    }
    return ret;
}

int main()
{
    std::string s = "Given the existence as";
    Vec<Str> v = split(s);
    for (Vec<Str>::size_type i = 0; i != v.size(); ++i)
        std::cout << v[i] << '\n';

    return 0;
}