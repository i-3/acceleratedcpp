#include <algorithm>
using std::sort;

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;

istream &read(istream &is, vector<string> &w)
{
    string s;
    cout << "Please enter words:" << endl;
    while (is >> s)
        w.push_back(s);
    cout << endl;
    return is;
}

int main()
{
    vector<string> words;
    read(cin, words);
    sort(words.begin(), words.end());
    typedef vector<double>::size_type vec_sz;
    vec_sz size = words.size();
    int i = 0;
    string w;
    int q;

    while (i != size)
    {
        if (i == 0)
        {
            w = words[0];
            q = 1;
        }
        else
        {
            if (w == words[i])
                ++q;
            else
            {
                cout << w << " - " << q << endl;
                w = words[i];
                q = 1;
            }
        }
        ++i;
    }
    cout << w << " - " << q << endl;

    return 0;
}