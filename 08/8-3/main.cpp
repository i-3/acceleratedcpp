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
template <class In>
int median(In b, In e)
{
    typedef typename vector<int>::size_type vec_sz;
    vec_sz size = e - b;
    if (size == 0)
        throw domain_error("median of an empty vector");
    sort(b, e);
    vec_sz mid = size / 2;
    return size % 2 == 0 ? (*(b + mid) + *(b + mid - 1)) / 2 : *(b + mid);
}

int main()
{
    vector<int> v = {0, 1, 2, 3, 4};
    cout << median(v.begin(), v.end()) << endl;
    return 0;
}