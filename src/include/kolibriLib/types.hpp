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

        /// @brief 
        /// @param p 
        /// @return 
        point<T> &operator=(const point<T> &p);

        point<T> &operator+(const point<T> &p);

        point<T> &operator-(const point<T> &p);

        /// @brief 
        /// @param a 
        /// @return 
        bool operator==(const point<T> &a) const;
        
        /// @brief Сравнивает равны ли обе координаты(x и y) какому либо числу
        /// @param a число
        /// @return 
        bool operator==(const T& a) const;

        /// @brief 
        /// @param a 
        /// @return 
        bool operator!=(const point<T> &a) const;

        /// @brief Сравнивает неравны ли обе координаты(x и y) какому либо числу
        /// @param a число
        /// @return
        bool operator!=(const T &a) const;
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


} // namespace KolibriLib

#endif // __TYPES_H__