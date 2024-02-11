#ifndef __TYPES_H__
#define __TYPES_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    template <class T>
    /// @brief Просто точка
    /// @paragraph Если необходимо использовать конкретный теип данных для точки используйте шаблоны. Например: point<uint64_t> p;
    struct point
    {
        T x;
        T y;

        point<T> &operator=(const point<T> &p)
        {
            x = p.x;
            y = p.y;
            return *this;
        }

        bool operator==(const point<T> &a) const
        {
            return x == a.x && y == a.y;
        }
        bool operator!=(const point<T> &a) const
        {
            return x != a.x || y != a.y;
        }
    };

    namespace UI
    {
        /// @brief Размер
        typedef point<unsigned> Size;
        typedef point<int> Coord;
    } // namespace UI

    namespace Colors
    {
        /// @brief Таблица цветов
        typedef ksys_colors_table_t ColorsTable;
    } // namespace Colors
    
    
} // namespace KolibriLib


#endif // __TYPES_H__