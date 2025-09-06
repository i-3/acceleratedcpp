#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;
using std::string;

typedef vector<string> v_type;

v_type in = {"an", "example", "to", "illustrate", "reverse"};

int main()
{
    v_type::size_type s = in.size();
    string::size_type max = 0;
    string longest = "";
    for (v_type::size_type i = 0; i != s; ++i)
    {
        string::size_type j = 0;
        string::size_type length = in[i].length();
        bool has = false;

        while (j != length)
        {
            char l = in[i][j];
            if (l == 'b' || l == 'd' || l == 'f' || l == 'h' ||
                l == 'k' || l == 'l' || l == 't' || l == 'g' ||
                l == 'j' || l == 'p' || l == 'q' || l == 'y')
                has = true;
            ++j;
        }
        if (!has && max < length)
        {
            max = length;
            longest = in[i];
        }
    }
    cout << longest << endl;
    return 0;
}