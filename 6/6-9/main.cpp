#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<string> v = {"cruel ", "world!"};

int main()
{
    string s = "Hello, ";
    s = accumulate(v.begin(), v.end(), s);
    cout << s << endl;
    return 0;
}