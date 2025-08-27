#include <iostream>
#include <map>
using namespace std;

int main()
{
    string s;
    map<string, int> counters;
    while (cin >> s)
        ++counters[s];
    // for (map<string, int>::const_iterator it = counters.begin();
    //      it != counters.end(); ++it)
    // {
    //     cout << it->first << "\t" << it->second << endl;
    // }

    multimap<int, string> MM;
    for (auto &it : counters)
    {
        MM.insert({it.second, it.first});
    }
    for (auto &it : MM)
    {
        cout << it.second << "\t" << it.first << endl;
    }

    return 0;
}