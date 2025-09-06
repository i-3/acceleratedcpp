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
typedef vector<Student_info> v_type;

v_type extract_fails(v_type &students)
{
    v_type fail;
    v_type::size_type i = 0;

    // while (i != students.size())
    // {
    //     if (students[i].grade < 60)
    //     {
    //         fail.push_back(students[i]);
    //         students.erase(students.begin() + i);
    //     }
    //     else
    //         ++i;
    // }

    v_type::size_type all = students.size();
    while (i != students.size())
    {
        if (students[i].grade < 60)
        {
            fail.push_back(students[i]);
            ++i;
        }
        else
        {
            students.insert(students.begin(), students[i]);
            i += 2;
        }
    }
    students.resize(all - fail.size());

    return fail;
}

int main()
{
    v_type s;
    int i = 0;
    while (i != 20000)
    {
        ++i;
        s.push_back({name : "Andrew", grade : 70});
        s.push_back({name : "Barbara", grade : 50});
    }
    v_type fail = extract_fails(s);
    cout << "pass: " << s.size() << endl;
    cout << "fail: " << fail.size() << endl;

    return 0;
}