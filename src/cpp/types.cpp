#include <kolibriLib/types.hpp>

using namespace KolibriLib;

template <class T>
KolibriLib::point<T>::point(T X, T Y)
{
    x = X;
    y = Y;
}

template <class T>
KolibriLib::point<T>::point(float f)
{
    x = f / 10.0;
    y = 10;

    if (x != y)
    {
//====================================================
        int num = x, denom = y, rem;
        if (num < denom)
        {
            int temp = num;
            num = denom;
            denom = temp;
        }
        while (rem = num % denom)
        {
            num = denom;
            denom = rem;
        }
//====================================================
        x /= rem;
        y /= rem;

    }
    else
    {
        x = 1;
        y = 1;
    }
    
}

template <class T>
ksys_pos_t KolibriLib::point<T>::GetKsysPost() const
{
    ksys_pos_t p;
    p.x = (uint16_t)x;
    p.y = (uint16_t)y;
    return p;
}

template <class T>
point<T> &KolibriLib::point<T>::operator+(const point<T> &a)
{
	x += a.x;
    y += a.y;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator-(const point<T> &a)
{
	x -= a.x;
    y -= a.y;
    return *this;
}

template <class T>
point<T> &KolibriLib::point<T>::operator=(const point<T> &p)
{
    x = p.x;
    y = p.y;
    return *this;
}


template <class T>
point<T> &point<T>::operator+=(const T &p)
{
    x += p;
    y += p;
    return *this;
}

template <class T>
point<T> &point<T>::operator-=(const T &p)
{
    x -= p;
    y -= p;
    return *this;
}

template <class T>
point<T> &point<T>::operator*=(const T &p)
{
    x *= p;
    y *= p;
    return *this;
}

template <class T>
point<T> &point<T>::operator/=(const T &p)
{
    x /= p;
    y /= p;
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