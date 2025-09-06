#include <algorithm>
#include <iostream>
using namespace std;

template <class Iter>
double median(Iter b, Iter e)
{
    ptrdiff_t size = e - b;
    if (size == 0)
        throw domain_error("median of an empty container");
    double c[size];
    copy(b, e, c);
    sort(c, c + size);
    ptrdiff_t mid = size / 2;
    return size % 2 == 0 ? (*(c + mid) + *(c + mid - 1)) / 2 : *(c + mid);
}
int main()
{
    double a[] = {9.9, 1.1, 3.3, 2.2, 1.1, 8.8};
    ptrdiff_t size = 5;

    double a2[size];
    copy(a, a + size, a2);
    double m = median(a2, a2 + size);
    bool same = equal(a, a + size, a2);

    sort(a2, a2 + size);
    ptrdiff_t mid = size / 2;
    double m2 = size % 2 == 0 ? (*(a2 + mid) + *(a2 + mid - 1)) / 2 : *(a2 + mid);

    if (m == m2 && same)
        cout << "correctly" << endl;
    return 0;
}