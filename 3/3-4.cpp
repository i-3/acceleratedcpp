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
    string s;
    string::size_type longest = 0;
    string::size_type shortest = 100;

    while (cin >> s)
    {
        if (longest < s.size())
            longest = s.size();
        if (shortest > s.size())
            shortest = s.size();
    }
    cout << "longest - " << longest << endl;
    cout << "shortest - " << shortest << endl;
    return 0;
}