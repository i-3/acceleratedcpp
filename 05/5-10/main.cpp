#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<string> v_type;

v_type dict = {"rotator", "example", "to", "level", "framing"};

int main()
{
    v_type::size_type s = dict.size();
    string pal;
    string::size_type max = 0;
    for (v_type::size_type i = 0; i != s; ++i)
    {
        string str = dict[i];
        string rev = string(str.rbegin(), str.rend());
        if (rev == str && max < str.length())
        {
            max = str.length();
            pal = str;
        }
    }
    cout << pal << endl;
    return 0;
}