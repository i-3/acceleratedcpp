#include <vector>
#include <list>
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

// Vec<string> p = {"this is an", "example", "to", "illustrate", "framing"};
string::size_type width(const Vec<string> &v)
{
    string::size_type maxlen = 0;
    for (Vec<string>::size_type i = 0; i != v.size(); ++i)
        maxlen = max(maxlen, v[i].size());
    return maxlen;
}
Vec<string> frame(const Vec<string> &v)
{
    Vec<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');
    ret.push_back(border);
    for (Vec<string>::size_type i = 0; i != v.size(); ++i)
    {
        ret.push_back("* " + v[i] +
                      string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.push_back(border);
    return ret;
}
Vec<string> vcat(const Vec<string> &top, const Vec<string> &bottom)
{
    Vec<string> ret = top;
    for (Vec<string>::const_iterator it = bottom.begin();
         it != bottom.end(); ++it)
        ret.push_back(*it);
    // ret.insert(ret.end(), bottom.begin(), bottom.end());

    return ret;
}
Vec<string> hcat(const Vec<string> &left, const Vec<string> &right)
{
    Vec<string> ret;
    string::size_type width1 = width(left) + 1;
    Vec<string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size())
    {
        string s;
        if (i != left.size())
            s = left[i++];
        s += string(width1 - s.size(), ' ');
        if (j != right.size())
            s += right[j++];
        ret.push_back(s);
    }
    return ret;
}

int main()
{
    Vec<string> p;
    p.push_back("this is an");
    p.push_back("example");
    p.push_back("to");
    p.push_back("illustrate");
    p.push_back("framing");

    // vector<string> conc = vcat(p, frame(p));
    Vec<string> conc = hcat(p, frame(p));

    for (Vec<string>::size_type i = 0; i != conc.size(); ++i)
    {
        cout << conc[i] << endl;
    }

    return 0;
}