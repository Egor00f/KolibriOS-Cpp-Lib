#include "types.hpp"

using namespace KolibriLib;


template <class T>
inline point<T> &KolibriLib::point<T>::operator=(const point<T> &p)
{
    x = p.x;
    y = p.y;
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