#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

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
class Ptr
{
public:
    void make_unique()
    {
        if (*refptr != 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p ? p->clone() : 0;
        }
    }

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

class Student_info
{
public:
    Student_info() {}
    Student_info(std::istream &is) { read(is); }

    std::string name() const
    {
        if (cp)
            return cp->name();
        else
            throw std::runtime_error("uninitialized Student");
    }
    double grade() const
    {
        if (cp)
            return cp->grade();
        else
            throw std::runtime_error("uninitialized Student");
    }
    static bool compare(const Student_info &s1, const Student_info &s2)
    {
        return s1.name() < s2.name();
    }
    std::istream &read(std::istream &);

private:
    Ptr<Core> cp;
};
std::istream &Student_info::read(std::istream &is)
{
    char ch;
    is >> ch;

    // allocate new object of the appropriate type
    // use Handle<T>(T*) to build a Handle<Core> from the pointer to that object
    // call Handle<T>::operator= to assign the Handle<Core> to the left-hand side
    if (ch == 'U')
        cp = new Core(is);
    else
        cp = new Grad(is);
    return is;
}

int main()
{
    Student_info s1;
    s1.read(std::cin);

    Student_info s2 = s1;
    s2.read(std::cin);

    std::cout << s1.name() << '\n';
    std::cout << s2.name() << '\n';

    return 0;
}