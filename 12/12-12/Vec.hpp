#ifndef GUARD_Vec
#define GUARD_Vec

#include <memory>
#include <iostream>
#include <cstring>

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

    Vec(const_iterator i, const_iterator j) { create(i, j); }

    T &operator[](size_type i) { return data[i]; }
    const T &operator[](size_type i) const { return data[i]; }

    void push_back(const T &val)
    {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    void insert(iterator pos, iterator in)
    {
        size_type new_size = limit - data + std::strlen(in);
        iterator new_data = alloc.allocate(new_size);

        iterator new_avail = std::uninitialized_copy(data, pos, new_data);
        new_avail = std::uninitialized_copy(in, in + std::strlen(in), new_avail);
        new_avail = std::uninitialized_copy(pos, avail, new_avail);

        uncreate();
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
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

    std::allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    void uncreate();
    void grow();
    void unchecked_append(const T &);
};

#endif