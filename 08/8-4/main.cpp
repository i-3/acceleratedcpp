#include <vector>
#include <iostream>
using namespace std;

template <class Bi>
void reverse(Bi beg, Bi end)
{
    while (beg != end)
    {
        // --end;
        if (beg != --end)
        {
            // swap(*beg++, *end);
            int b = *beg;
            *beg++ = *end, *end = b;
        }
    }
}

int main()
{
    vector<int> v = {0, 1, 2, 3, 4};
    reverse(v.begin(), v.end());
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}