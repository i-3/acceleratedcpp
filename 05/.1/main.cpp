#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iostream>
using std::cout;
using std::endl;

struct Student_info
{
    std::string name;
    double grade;
};
bool fgrade(const Student_info &s)
{
    return s.grade < 60;
}
// vector<Student_info> extract_fails(vector<Student_info> &students)
// {
// vector<Student_info> pass, fail;
// for (vector<Student_info>::size_type i = 0;
//      i != students.size(); ++i)
//     if (fgrade(students[i]))
//         fail.push_back(students[i]);
//     else
//         pass.push_back(students[i]);
// students = pass;

// vector<Student_info> fail;
// vector<Student_info>::size_type i = 0;
// while (i != students.size())
// {
//     if (fgrade(students[i]))
//     {
//         fail.push_back(students[i]);
//         students.erase(students.begin() + i);
//     }
//     else
//         ++i;
// }

// vector<Student_info> fail;
// vector<Student_info>::iterator iter = students.begin();
// while (iter != students.end())
// {
//     if (fgrade(*iter))
//     {
//         fail.push_back(*iter);
//         iter = students.erase(iter);
//     }
//     else
//         ++iter;
// }

//     return fail;
// }

list<Student_info> extract_fails(list<Student_info> &students)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (fgrade(*iter))
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
    // vector<Student_info> s;
    list<Student_info> s;
    int i = 0;
    while (i != 20)
    {
        ++i;
        s.push_back({name : "Andrew", grade : 70});
        s.push_back({name : "Barbara", grade : 50});
    }
    // vector<Student_info> fail = extract_fails(s);
    list<Student_info> fail = extract_fails(s);
    cout << "pass: " << s.size() << endl;
    cout << "fail: " << fail.size() << endl;

    return 0;
}