#include <algorithm>
using std::sort;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

#include <vector>
using std::vector;

int main()
{
    cout << "Enter words, "
            "followed by end-of-file: ";
    vector<string> words;
    string x;
    while (cin >> x)
        words.push_back(x);
    cout << endl;
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