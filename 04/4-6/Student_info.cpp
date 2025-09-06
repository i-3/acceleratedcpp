#include "Student_info.h"
// #include "grade.h"
#include "median.h"
using std::cout;
using std::domain_error;
using std::endl;
using std::istream;
using std::vector;

double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
        throw domain_error("student has done no homework");
    // return grade(midterm, final, median(hw));
    double med = median(hw);
    return 0.2 * midterm + 0.4 * final + 0.4 * med;
}
bool compare(const Student_info &x, const Student_info &y)
{
    return x.name < y.name;
}
istream &read(istream &is, Student_info &s)
{
    double midterm, final;
    std::vector<double> homework;
    // is >> s.name >> s.midterm >> s.final;
    // read_hw(is, s.homework);
    is >> s.name >> midterm >> final;
    read_hw(is, homework);

    if (homework.size())
        s.grade = grade(midterm, final, homework);

    return is;
}
istream &read_hw(istream &in, vector<double> &hw)
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