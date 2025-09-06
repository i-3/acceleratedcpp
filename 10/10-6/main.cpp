#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class String_list
{
    std::list<string> Ls;

public:
    typedef list<string>::iterator it;
    it begin() { return Ls.begin(); }
    it end() { return Ls.end(); }

    void push_back(string s)
    {
        Ls.push_back(s);
    };
};

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}

int main()
{
    String_list sl;
    const string str = "Hello, world!";

    typedef string::const_iterator iter;
    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);
        iter j = find_if(i, str.end(), space);
        if (i != str.end())
            sl.push_back(string(i, j));
        i = j;
    }

    for (auto i : sl)
        std::cout << i << "\n";

    return 0;
}