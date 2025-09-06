#include <vector>
#include <iostream>
using namespace std;

// template <class In, class X>
// In find(In begin, In end, const X &x)
// {
//     while (begin != end && *begin != x)
//         ++begin;
//     return begin;
// }
template <class In, class X>
In find(In begin, In end, const X &x)
{
    if (begin == end || *begin == x)
        return begin;
    begin++;
    return find(begin, end, x);
}

template <class In, class Out>
Out _copy(In begin, In end, Out dest)
{
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

template <class For, class X>
void replace(For beg, For end, const X &x, const X &y)
{
    while (beg != end)
    {
        if (*beg == x)
            *beg = y;
        ++beg;
    }
}

template <class Bi>
void reverse(Bi begin, Bi end)
{
    while (begin != end)
    {
        --end;
        if (begin != end)
            swap(*begin++, *end);
    }
}

template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X &x)
{
    while (begin < end)
    {
        Ran mid = begin + (end - begin) / 2;
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
        else
            return true;
    }
    return false;
}

int main()
{
    vector<int> vi = {0, 1, 2, 3, 4};

    // vector<int>::const_iterator it = find(vi.begin(), vi.end(), 2);
    // cout << *it << endl;

    // vector<int> vi2;
    // _copy(vi.begin(), vi.end(), back_inserter(vi2));
    // for (auto i : vi2)
    //     cout << i << " ";
    // cout << endl;

    // replace(vi.begin(), vi.end(), 2, 1);
    // for (auto i : vi)
    //     cout << i << " ";
    // cout << endl;

    // reverse(vi.begin(), vi.end());
    // for (auto i : vi)
    //     cout << i << " ";
    // cout << endl;

    bool is = binary_search(vi.begin(), vi.end(), 4);
    cout << is << endl;

    return 0;
}