#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef string::const_iterator SI;

bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";
    return !(isalnum(c) ||
             find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}
SI url_beg(SI b, SI e)
{
    static const string sep = "://";
    SI i = b;
    while ((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        if (i != b && i + sep.size() != e)
        {
            SI beg = i;
            while (beg != b && isalpha(beg[-1]))
                --beg;
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        i += sep.size();
    }
    return e;
}
SI url_end(SI b, SI e)
{
    return find_if(b, e, not_url_char);
}
vector<string> find_urls(const string &s)
{
    vector<string> ret;
    SI b = s.begin(), e = s.end();
    while (b != e)
    {
        b = url_beg(b, e);
        if (b != e)
        {
            SI after = url_end(b, e);
            ret.push_back(string(b, after));
            b = after;
        }
    }
    return ret;
}
string text = "The function executes by placing two iterators into the string delimited by b and e: text http://www.acceleratedcpp.com more text";
int main()
{
    vector<string> out = find_urls(text);
    cout << out[0] << endl;
    return 0;
}