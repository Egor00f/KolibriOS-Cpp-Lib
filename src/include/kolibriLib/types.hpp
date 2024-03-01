#ifndef __TYPES_H__
#define __TYPES_H__

#include <sys/ksys.h>

#define X_Y(x, y)(((x) << 16) | (y))

namespace KolibriLib
{
    template <class T>
    /// @brief Просто точка
    /// @paragraph Если необходимо использовать конкретный теип данных для точки используйте шаблоны. Например: point<uint64_t> p;
    struct point
    {
        /// @brief координата по оси X, или ширина
        T x;
        /// @brief координата по оси Y, или высота
        T y;

        /// @brief Конструктор
        /// @param X 
        /// @param Y 
        point(T X = (T)0, T Y = (T)0);

        /// @brief Точка как отношение x/y
        /// @param f Десятичная дробь, которая ≈ x/y
        point(float f);

        ksys_pos_t GetKsysPost() const;

        point<T>& operator+(const point<T> &a);
        point<T> &operator-(const point<T> &a);

        /// @brief 
        /// @param p 
        /// @return 
        point<T> &operator=(const point<T> &p);

        /// @brief Прибавить к обоим кординатам значение
        /// @tparam B 
        /// @param p 
        /// @return 
        point<T> &operator+=(const T &p);

        point<T> &operator-=(const T &p);

        point<T> &operator*=(const T &p);

        point<T> &operator/=(const T &p);

        /// @brief 
        /// @param a 
        /// @return 
        bool operator==(const point<T> &a) const;
        

        /// @brief 
        /// @param a 
        /// @return 
        bool operator!=(const point<T> &a) const;
    };

    namespace UI
    {
        /// @brief Размер
        typedef point<unsigned> Size;
        typedef point<int> Coord;
    } // namespace UI

    namespace Colors
    {
        
    } // namespace Colors

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

} // namespace KolibriLib

#endif // __TYPES_H__