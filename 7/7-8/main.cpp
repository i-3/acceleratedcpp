#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef vector<string> Vs;

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}
Vs split(const string &str)
{
    typedef string::const_iterator iter;
    Vs ret;
    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);
        iter j = find_if(i, str.end(), space);
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}
bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*’(),";
    return !(isalnum(c) ||
             find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}
string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}
string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
    static const string sep = "://";
    typedef string::const_iterator iter;
    iter i = b;
    while ((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        if (i != b && i + sep.size() != e)
        {
            iter beg = i;
            while (beg != b && isalpha(beg[-1]))
                --beg;
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        i += sep.size();
    }
    return e;
}
vector<string> find_urls(const string &s)
{
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();
    while (b != e)
    {
        b = url_beg(b, e);
        if (b != e)
        {
            iter after = url_end(b, e);
            ret.push_back(string(b, after));
            b = after;
        }
    }
    return ret;
}
map<string, vector<int>> xref(istream &in, Vs find_words(const string &) = split)
{
    string line;
    int line_number = 0;
    map<string, vector<int>> ret;
    while (getline(in, line))
    {
        ++line_number;
        Vs words = find_words(line);
        for (Vs::const_iterator it = words.begin(); it != words.end(); ++it)
            if (find(ret[*it].begin(), ret[*it].end(), line_number) == ret[*it].end())
                ret[*it].push_back(line_number);
    }
    return ret;
}

int main()
{
    map<string, vector<int>> ret = xref(cin, find_urls);
    for (map<string, vector<int>>::const_iterator it = ret.begin();
         it != ret.end(); ++it)
    {
        string str = it->second.size() == 1 ? " occurs on line " : " occurs on lines: ";
        cout << it->first << str;
        vector<int>::const_iterator line_it = it->second.begin();
        cout << *line_it;
        ++line_it;
        while (line_it != it->second.end())
        {
            cout << ", " << *line_it;
            ++line_it;
        }
        cout << endl;
    }
    return 0;
}