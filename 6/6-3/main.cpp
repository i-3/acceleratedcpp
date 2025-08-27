#include <vector>
#include <iostream>
using namespace std;

typedef vector<int>::iterator VIi;

int main()
{
    vector<int> u(10, 100);
    vector<int> v;
    copy(u.begin(), u.end(), v.begin());

    for (VIi i = v.begin(); i != v.end(); ++i)
        cout << *i << endl;
    return 0;
}