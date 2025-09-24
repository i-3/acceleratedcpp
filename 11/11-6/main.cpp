#include <vector>
#include <iostream>
#include <memory>
using namespace std;

template <class T>
class Vec
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;

    Vec() { create(); }
    explicit Vec(size_type n, const T &val = T()) { create(n, val); }

    Vec(const Vec &v) { create(v.begin(), v.end()); }
    Vec &operator=(const Vec &);
    ~Vec() { uncreate(); }

    T &operator[](size_type i) { return data[i]; }
    const T &operator[](size_type i) const { return data[i]; }

    void push_back(const T &val)
    {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    iterator erase_(T *);
    iterator erase_(T *, T *);
    void clear_();

    size_type size() const { return avail - data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    void uncreate();
    void grow();
    void unchecked_append(const T &);
};

template <class T>
Vec<T> &Vec<T>::operator=(const Vec &rhs)
{
    if (&rhs != this)
    {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}
template <class T>
void Vec<T>::create()
{
    data = avail = limit = 0;
}
template <class T>
void Vec<T>::create(size_type n, const T &val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}
template <class T>
void Vec<T>::uncreate()
{
    if (data)
    {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = 0;
}
template <class T>
void Vec<T>::grow()
{
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}
template <class T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}

template <class T>
T *Vec<T>::erase_(T *iter)
{
    size_type new_size = avail - data - 1;
    iterator new_data = alloc.allocate(new_size);
    iterator it = data;
    iterator new_it = new_data;
    while (it != avail)
    {
        if (it != iter)
            alloc.construct(new_it++, *it);
        it++;
    }
    uncreate();
    data = new_data;
    avail = new_data + new_size;

    return avail;
}
template <class T>
T *Vec<T>::erase_(T *iter, T *iter2)
{
    size_type new_size = avail - data - (iter2 - iter);
    iterator new_data = alloc.allocate(new_size);
    iterator it = data;
    iterator new_it = new_data;
    while (it != avail)
    {
        if ((iter - it) > 0 || (it - iter2) >= 0)
            alloc.construct(new_it++, *it);
        it++;
    }
    uncreate();
    data = new_data;
    avail = new_data + new_size;

    return avail;
}
template <class T>
void Vec<T>::clear_()
{
    uncreate();
}

int main()
{
    Vec<string> vs;
    vs.push_back("one");
    vs.push_back("two");
    vs.push_back("three");

    // vs.erase_(vs.begin());
    // vs.erase_(vs.begin(), vs.begin() + 2);
    // for (auto s : vs)
    //     cout << s << "\n";

    vs.clear_();
    cout << vs.size() << "\n";

    return 0;
}
