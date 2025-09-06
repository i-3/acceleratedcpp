#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;
using std::string;

typedef vector<string> v_type;

v_type in = {"An", "examplE", "TO", "illustrate", "framing"};

int main()
{
    v_type::size_type s = in.size();
    v_type up;
    v_type lo;
    for (v_type::size_type i = 0; i != s; ++i)
    {
        string::size_type j = 0;
        string::size_type length = in[i].length();
        bool isup = false;
        while (j != length)
        {
            if (isupper(in[i][j]))
                isup = true;
            ++j;
        }
        isup ? up.push_back(in[i]) : lo.push_back(in[i]);
    }
    lo.insert(lo.end(), up.begin(), up.end());
    for (v_type::size_type i = 0; i != lo.size(); ++i)
        cout << lo[i] << endl;
    return 0;
}