#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iostream>
using std::cout;
using std::endl;
using std::string;

using std::max;

vector<string> picture = {
    "*",
    "*****",
    "*********",
    "*************"};
typedef vector<string>::size_type s_type;
vector<string> center(const vector<string> &v)
{
    s_type s = v.size();
    string::size_type maxlen = 0;
    for (s_type i = 0; i != s; ++i)
        maxlen = max(maxlen, v[i].length());
    vector<string> symmetric;
    for (s_type i = 0; i != s; ++i)
    {
        symmetric.push_back(string((maxlen - v[i].length()) / 2, ' ') + v[i]);
    }
    return symmetric;
}

int main()
{
    vector<string> x = center(picture);
    s_type i = 0;
    while (i != x.size())
    {
        cout << x[i] << endl;
        ++i;
    }
    return 0;
}