#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;
using std::vector;

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
    typedef vector<double>::size_type vec_sz;
    vec_sz size = words.size();
    cout << size << endl;

    return 0;
}