#include <vector>
using std::vector;

#include <list>
using std::list;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

using std::max;

vector<string> p = {"this is an", "example", "to", "illustrate", "framing"};
string::size_type width(const vector<string> &v)
{
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i)
        maxlen = max(maxlen, v[i].size());
    return maxlen;
}
vector<string> frame(const vector<string> &v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');
    string pad = "* " + string(maxlen, ' ') + " *";
    ret.insert(ret.begin(), {border, pad});
    for (vector<string>::size_type i = 0; i != v.size(); ++i)
    {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.insert(ret.end(), {pad, border});
    return ret;
}

int main()
{
    vector<string> f = frame(p);
    for (vector<string>::size_type i = 0; i != f.size(); ++i)
    {
        cout << f[i] << endl;
    }
    return 0;
}