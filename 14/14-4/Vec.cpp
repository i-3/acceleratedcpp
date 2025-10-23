#include "Vec.hpp"

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
    std::uninitialized_fill(data, limit, val);
}
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
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
    // size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
    size_type new_size = limit - data + 1;

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
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