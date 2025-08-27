#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct Student_info
{
    string name;
    double midterm, final;
    vector<double> homework;
};
typedef vector<Student_info> Vsi;

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
istream &read(istream &is, Student_info &s)
{
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework);
    return is;
}
bool did_all_hw(const Student_info &s)
{
    return (find(s.homework.begin(), s.homework.end(), 0) == s.homework.end());
}
double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}
double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();
    if (size == 0)
        throw domain_error("median of an empty vector");
    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}
double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}
double grade(const Student_info &s)
{
    return grade(s.midterm, s.final, s.homework);
}
double grade_aux(const Student_info &s)
{
    try
    {
        return grade(s);
    }
    catch (domain_error)
    {
        return grade(s.midterm, s.final, 0);
    }
}
// double median_analysis(const Vsi &students)
// {
//     vector<double> grades;
//     transform(students.begin(), students.end(),
//               back_inserter(grades), grade_aux);
//     return median(grades);
// }

double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}
// double average_analysis(const Vsi &students)
// {
//     vector<double> grades;
//     transform(students.begin(), students.end(),
//               back_inserter(grades), average_grade);
//     return median(grades);
// }

double optimistic_median(const Student_info &s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(),
                back_inserter(nonzero), 0);
    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}
// double optimistic_median_analysis(const Vsi &students)
// {
//     vector<double> grades;
//     transform(students.begin(), students.end(),
//               back_inserter(grades), optimistic_median);
//     return median(grades);
// }

template <class Func>
double analysis(const Vsi &students, Func &func)
{
    vector<double> grades;
    transform(students.begin(), students.end(),
              back_inserter(grades), func);
    return median(grades);
}

void write_analysis(ostream &out, const string &name,
                    double (*f)(const Student_info &),
                    const Vsi &did,
                    const Vsi &didnt)
{
    out << name << ": median(did) = " << analysis(did, f)
        << ", median(didnt) = " << analysis(didnt, f) << endl;
}

int main()
{
    Vsi did, didnt;
    Student_info student;
    while (read(cin, student))
    {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    if (did.empty())
    {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if (didnt.empty())
    {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }
    write_analysis(cout, "median", grade_aux, did, didnt);
    write_analysis(cout, "average", average_grade, did, didnt);
    write_analysis(cout, "median of homework turned in", optimistic_median, did, didnt);
    return 0;
}