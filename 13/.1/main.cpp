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
bool compare(const Core &c1, const Core &c2)
{
    return c1.name() < c2.name();
}
std::string Core::name() const
{
    return n;
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
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
class Student_info
{
public:
    Student_info() : cp(0) {}
    Student_info(std::istream &is) : cp(0) { read(is); }
    Student_info(const Student_info &);
    Student_info &operator=(const Student_info &);
    ~Student_info() { delete cp; }

    std::istream &read(std::istream &);

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

private:
    Core *cp;
};
Student_info::Student_info(const Student_info &s) : cp(0)
{
    if (s.cp)
        cp = s.cp->clone();
}
Student_info &Student_info::operator=(const Student_info &s)
{
    if (&s != this)
    {
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}
std::istream &Student_info::read(std::istream &is)
{
    delete cp;
    char ch;
    is >> ch;
    if (ch == 'U')
    {
        cp = new Core(is);
    }
    else
    {
        cp = new Grad(is);
    }
    return is;
}

int main()
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    while (record.read(std::cin))
    {
        maxlen = std::max(maxlen, record.name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), Student_info::compare);

    for (std::vector<Student_info>::size_type i = 0;
         i != students.size(); ++i)
    {
        std::cout << students[i].name()
                  << std::string(maxlen + 1 - students[i].name().size(), ' ');
        try
        {
            double final_grade = students[i].grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
                      << std::setprecision(prec) << '\n';
        }
        catch (std::domain_error e)
        {
            std::cout << e.what() << '\n';
        }
    }
    return 0;
}