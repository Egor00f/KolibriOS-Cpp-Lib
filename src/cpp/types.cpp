#include <kolibriLib/types.hpp>

using namespace KolibriLib;

template <class T>
ksys_pos_t KolibriLib::point<T>::GetKsysPost() const
{
    ksys_pos_t p;
    p.x = (uint16_t)x;
    p.y = (uint16_t)y;
    return p;
}

template <class T>
point<T> &KolibriLib::point<T>::operator=(const point<T> &p)
{
    x = p.x;
    y = p.y;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator+(const point<T> &p)
{
    x += p.x;
    y += p.y;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator-(const point<T> &p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator/(const int &p)
{
    x /= p;
    y /= p;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator*(const int &p)
{
    x *= x;
    y *= y;
    return *this;
}

template <class T>
bool KolibriLib::point<T>::operator==(const point<T> &a) const
{
    return x == a.x && y == a.y;
}

template <class T>
bool KolibriLib::point<T>::operator!=(const point<T> &a) const
{
    return x != a.x || y != a.y;
}