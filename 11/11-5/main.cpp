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

    Student_info() { create(); }
    std::istream &copy(std::istream &);
    Student_info &operator=(Student_info &);
    ~Student_info() { uncreate(); }

private:
    void create();
    void uncreate();
};
int created = 0;
void Student_info::create()
{
    midterm = final = 0;
    ++created;
}
int copied = 0;
istream &Student_info::copy(istream &in)
{
    in >> name >> midterm >> final;
    if (in)
    {
        double x;
        while (in >> x)
            homework.push_back(x);
        in.clear();
    }
    ++copied;
    return in;
}
int assigned = 0;
Student_info &Student_info::operator=(Student_info &rhs)
{
    if (&rhs != this)
    {
        Student_info(rhs);
    }
    ++assigned;
    return *this;
}
int destroyed = 0;
void Student_info::uncreate()
{
    ++destroyed;
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
double median_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(),
              back_inserter(grades), grade_aux);
    return median(grades);
}

double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}
double average_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(),
              back_inserter(grades), average_grade);
    return median(grades);
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
double optimistic_median_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(),
              back_inserter(grades), optimistic_median);
    return median(grades);
}

void write_analysis(ostream &out, const string &name,
                    double analysis(const vector<Student_info> &),
                    const vector<Student_info> &did,
                    const vector<Student_info> &didnt)
{
    out << name << ": median(did) = " << analysis(did)
        << ", median(didnt) = " << analysis(didnt) << endl;
}

int main()
{
    vector<Student_info> did, didnt;
    Student_info student;

    Student_info student2;
    student = student2;
    student = student2;

    while (student.copy(cin))
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
    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in",
                   optimistic_median_analysis, did, didnt);

    cout << "created: " << created << endl;
    cout << "copied: " << copied << endl;
    cout << "assigned: " << assigned << endl;
    cout << "destroyed: " << destroyed << endl;

    return 0;
}