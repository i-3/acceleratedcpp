#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

// template <class T>
// T median(vector<T> v)
// {
//     typedef typename vector<T>::size_type vec_sz;
//     vec_sz size = v.size();
//     if (size == 0)
//         throw domain_error("median of an empty vector");
//     sort(v.begin(), v.end());
//     vec_sz mid = size / 2;
//     return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
// }
// int main()
// {
//     vector<int> vi = {0, 1, 2, 3, 4};
//     int m = median(vi);
//     cout << m << endl;
//     return 0;
// }

template <class Iter>
double median(Iter b, Iter e)
{
    ptrdiff_t size = e - b;
    if (size == 0)
        throw domain_error("median of an empty container");
    sort(b, e);
    ptrdiff_t mid = size / 2;
    return size % 2 == 0 ? (*(b + mid) + *(b + mid - 1)) / 2 : *(b + mid);
}
int main()
{
    vector<int> v = {9, 1, 3, 2, 1};
    double a[] = {9.9, 1.1, 3.3, 2.2, 1.1};

    // cout << median(v.begin(), v.end()) << endl;
    cout << median(a, a + 5) << endl;
    return 0;
}