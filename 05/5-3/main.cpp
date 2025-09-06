#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iostream>
using std::cout;
using std::endl;
using std::string;

struct Student_info
{
    std::string name;
    double grade;
};

// typedef vector<Student_info> c_type;
typedef list<Student_info> c_type;

c_type fail;
int extract_fails(c_type &students)
{
    c_type::iterator iter = students.begin();
    while (iter != students.end())
    {
        if ((*iter).grade < 60)
        {
            fail.push_back(*iter);
            iter = students.erase(iter);
        }
        else
            ++iter;
    }
    return 0;
}

int main()
{
    c_type s;
    int i = 0;
    while (i != 20000)
    {
        ++i;
        s.push_back({name : "Andrew", grade : 70});
        s.push_back({name : "Barbara", grade : 50});
    }
    extract_fails(s);
    cout << "pass: " << s.size() << endl;
    cout << "fail: " << fail.size() << endl;
    return 0;
}