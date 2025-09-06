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
vector<Student_info> fail;
// list<Student_info> fail;
int extract_fails(vector<Student_info> &students)
// int extract_fails(list<Student_info> &students)
{
    vector<Student_info>::iterator iter = students.begin();
    // list<Student_info>::iterator iter = students.begin();
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
    vector<Student_info> s;
    // list<Student_info> s;
    int i = 0;
    while (i != 50000)
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