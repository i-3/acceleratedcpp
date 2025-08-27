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
double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}
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

double _analysis(const vector<Student_info> &students, const int &i)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades),
              i == 0 ? grade_aux : i == 1 ? average_grade
                                          : optimistic_median);
    return median(grades);
}

void write_analysis(ostream &out, const string &name,
                    double analysis(const vector<Student_info> &, const int &),
                    const vector<Student_info> &did,
                    const vector<Student_info> &didnt, const int &i)
{
    out << name << ": median(did) = " << analysis(did, i)
        << ", median(didnt) = " << analysis(didnt, i) << endl;
}

bool classify(const Student_info &s, bool criteria)
{
    if (criteria)
        return (find(s.homework.begin(), s.homework.end(), 0) == s.homework.end());
    else
        return grade(s) < 60;
}
vector<Student_info> extract_fails(vector<Student_info> &students)
{
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (classify(*iter, false))
        {
            fail.push_back(*iter);
            iter = students.erase(iter);
        }
        else
            ++iter;
    }
    return fail;
}

int main()
{
    // vector<Student_info> did, didnt;
    // Student_info student;
    // while (read(cin, student))
    // {
    //     if (classify(student, true))
    //         did.push_back(student);
    //     else
    //         didnt.push_back(student);
    // }

    // if (did.empty())
    // {
    //     cout << "No student did all the homework!" << endl;
    //     return 1;
    // }
    // if (didnt.empty())
    // {
    //     cout << "Every student did all the homework!" << endl;
    //     return 1;
    // }
    // write_analysis(cout, "median", _analysis, did, didnt, 0);
    // write_analysis(cout, "average", _analysis, did, didnt, 1);
    // write_analysis(cout, "median of homework turned in", _analysis, did, didnt, 2);

    vector<Student_info> s;
    Student_info student;
    while (read(cin, student))
        s.push_back(student);

    vector<Student_info> f = extract_fails(s);
    cout << "pass: " << s.size() << endl;
    cout << "fail: " << f.size() << endl;

    return 0;
}