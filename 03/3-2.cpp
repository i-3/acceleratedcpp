#include <algorithm>
using std::sort;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main()
{
    cout << "Enter integers, "
            "followed by end-of-file: ";
    vector<double> ints;
    double x;
    while (cin >> x)
        ints.push_back(x);
    cout << endl;

    typedef vector<double>::size_type vec_sz;
    vec_sz size = ints.size();
    sort(ints.begin(), ints.end());
    int s = size;
    int quartile = size / 4;

    while (s != 0)
    {
        --s;
        cout << ints[s] << " ";
        if (s % quartile == 0)
            cout << endl;
    }
    cout << endl;
    return 0;
}