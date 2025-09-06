// equal(b, e, b2)
// accumulate(b, e, t)
// find(b, e, t)
// find_if(b, e, p)
// search(b, e, b2, e2)
// copy(b, e, d)
// remove_copy(b, e, d, t)
// remove_copy_if(b, e, d, p)
// remove(b, e, t)
// transform(b, e, d, f)
// partition(b, e, p)

#include <iostream>
#include <vector>
using namespace std;

template <class In>
bool equal(In b, In e, In b2)
{
    while (b != e)
        if (*b++ != *b2++)
            return false;
    return true;
};
template <class In, class T>
T accumulate(In b, In e, T t)
{
    while (b != e)
        t += *b++;
    return t;
};
template <class In, class T>
In find(In b, In e, T t)
{
    while (b != e)
        if (t == *b)
            return b;
        else
            ++b;
    return e;
};
bool isnull(int i)
{
    return i == 0;
};
template <class In, class P>
In find_if(In b, In e, P p)
{
    while (b != e)
        if (p(*b))
            return b;
        else
            ++b;
    return e;
};
template <class In>
In search(In b, In e, In b2, In e2)
{
    while (b != e)
    {
        if (*b == *b2)
        {
            In beg = b + 1, beg2 = b2 + 1;
            while (beg2 != e2)
            {
                if (*beg != *beg2)
                    beg = b, beg2 = e2;
                else
                    ++beg, ++beg2;
            }
            if (beg != b)
                return b;
        }
        b++;
    }
    return e;
};
template <class In, class Out>
Out _copy(In b, In e, Out d)
{
    while (b != e)
        *d++ = *b++;
    return d - 1;
};
template <class In, class Out, class T>
Out remove_copy(In b, In e, Out d, T t)
{
    while (b != e)
        if (*b != t)
            *d++ = *b++;
        else
            b++;
    return d;
};
template <class In, class Out, class P>
Out remove_copy_if(In b, In e, Out d, P p)
{
    while (b != e)
        if (!p(*b))
            *d++ = *b++;
        else
            b++;
    return d;
};
template <class For, class T>
For remove(For b, For e, T t)
{
    For d = b;
    while (d != e && b != e)
    {
        if (*d != t)
            ++d;
        else if (*b == t || d >= b)
            ++b;
        else
            *d++ = *b, *b++ = 0;
    }
    return d - 1;
};
int Double(int i)
{
    return 2 * i;
}
template <class In, class Out, class F>
Out transform(In b, In e, Out d, F f)
{
    while (b != e)
        *d++ = f(*b++);
    return d - 1;
};
bool morethan_4(int i)
{
    return i > 4;
}
template <class For, class P>
For partition(For b, For e, P p)
{
    For B = b, E = e;
    while (b < e)
        if (p(*b))
            ++b;
        else if (!p(*(e - 1)))
            --e;
        else
        {
            int f = *b;
            *b = *(e - 1);
            *(e - 1) = f;
        }
    while (p(*B))
        ++B;
    return B;
};

int main()
{
    vector<int> vi = {1, 2, 0, 0, 6, 0, 7}, V = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> vd = {0.0, 1.3, 2.6};

    // cout << equal(vi.begin(), vi.end(), vi2.begin()) << endl;
    // cout << accumulate(vd.begin(), vd.end(), 10.0) << endl;
    // cout << *(find(vd.begin(), vd.end(), 1.3)) << endl;
    // cout << *(find_if(vi.begin(), vi.end(), isnull)) << endl;
    // cout << *(search(vi3.begin(), vi3.end(), v.begin(), v.end())) << endl;
    // cout << *(_copy(vi.begin(), vi.end(), v.begin())) << endl;
    // cout << *(remove_copy(vi.begin(), vi.end(), v.begin(), 2)) << endl;
    // cout << *(remove_copy_if(vi.begin(), vi.end(), v.begin(), isnull)) << endl;
    // cout << *(remove(vi.begin(), vi.end(), 0)) << endl;
    // cout << *(transform(v.begin(), v.end(), V.begin(), Double)) << endl;
    cout << *(partition(V.begin(), V.end(), morethan_4)) << endl;

    return 0;
}