#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iomanip>
using std::setw;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

using std::max;

#include <algorithm>
using std::sort;

typedef string::size_type s_type;
struct Rotate
{
    string permut;
    s_type index;
    s_type end;
};
string in1 = "The quick brown fox";
string in2 = "jumped over the fence";
vector<Rotate> r;

int gen(string s)
{
    s_type i = 0;
    s_type size = s.size();
    while (i != size)
    {
        if (i == 0 || isspace(s[i - 1]))
            r.push_back({permut : s.substr(i, s.size() - i) + " " + s.substr(0, i),
                         index : i ? i - 1 : 0,
                         end : size});
        ++i;
    }
    return 0;
}
bool compare(const Rotate &x, const Rotate &y)
{
    return x.permut < y.permut;
}

int main()
{
    gen(in1);
    gen(in2);
    sort(r.begin(), r.end(), compare);
    s_type s = r.size();
    for (s_type i = 0; i != s; ++i)
        cout << setw(20) << r[i].permut.substr(r[i].end - r[i].index, r[i].end)
             << "   " << r[i].permut.substr(0, r[i].end - r[i].index) << endl;

    return 0;
}