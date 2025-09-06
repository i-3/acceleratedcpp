#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
using namespace std;

// class Student_info
// {
// public:
//     Student_info();
//     Student_info(std::istream &);

//     std::string name() const { return n; }
//     bool valid() const { return !homework.empty(); }
//     std::istream &read(std::istream &);
//     double grade() const;

// private:
//     std::string n;
//     double midterm, final;
//     std::vector<double> homework;
// };
// Student_info::Student_info() : midterm(0), final(0) {}
// Student_info::Student_info(istream &is) { read(is); }

class String_list
{
    std::list<string> Ls;

public:
    String_list();

    int size() { return Ls.size(); }
};
// String_list::String_list() {}
String_list::String_list() : Ls({"", ""}) {}

int main()
{
    String_list x;
    cout << x.size() << endl;
    return 0;
}