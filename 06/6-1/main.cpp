#include <vector>
#include <iostream>
using namespace std;

typedef vector<string> VS;
typedef string::size_type SS;
typedef VS::const_iterator VI;
VS p = {"this is an", "example", "to", "illustrate", "framing"};

SS width(const VS &v)
{
    SS maxlen = 0;
    for (VI i = v.begin(); i != v.end(); ++i)
        maxlen = max(maxlen, (*i).size());
    return maxlen;
}
VS frame(const VS &v)
{
    VS ret;
    SS maxlen = width(v);
    string border(maxlen + 4, '*');
    ret.push_back(border);
    for (VI i = v.begin(); i != v.end(); ++i)
        ret.push_back("* " + *i + string(maxlen - (*i).size(), ' ') + " *");
    ret.push_back(border);
    return ret;
}
VS hcat(const VS &left, const VS &right)
{
    VS ret;
    SS width1 = width(left) + 1;
    VI li = left.begin(), ri = right.begin();
    while (li != left.end() || ri != right.end())
    {
        string s;
        if (li != left.end())
            s = *li++;
        s += string(width1 - s.size(), ' ');
        if (ri != right.end())
            s += *ri++;
        ret.push_back(s);
    }
    return ret;
}

int main()
{
    VS conc = hcat(p, frame(p));
    for (VI i = conc.begin(); i != conc.end(); ++i)
        cout << *i << endl;
    return 0;
}