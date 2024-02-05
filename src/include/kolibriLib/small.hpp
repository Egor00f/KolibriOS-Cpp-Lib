/*
    Файл с константами и малыми струтурами, которые используются везде
*/
#ifndef __SMALL_H__
#define __SMALL_H__

#include <string>

#define DEBUG true

namespace KolibriLib
{
    const std::string ConfigurationDir = "/kolibrios/etc/";

    const std::string ImgDir = ConfigurationDir + "images/";

    const std::string DefaultImage = ImgDir + "default.png";

    const std::string CursorsDir = ConfigurationDir + "cursors/"; // Предпологается что в этой папке лежат файлы, они заранее приготовленны

    template <class T>
    /// @brief Просто точка
    /// @paragraph Если необходимо использовать конкретный теип данных для точки используйте шаблоны. Например: point<uint64_t> p;
    struct point
    {
        T x;
        T y;


        point<T>& operator = ( const point<T>& p)
        {
            x = p.x;
            y = p.y;
            return *this;
        }

        bool operator == (const point<T>& a) const
        {
            return x == a.x && y == a.y;
        }
        bool operator != (const point<T>& a) const
        {
            return x != a.x || y != a.y;
        }
        
    };

} // namespace KolibriLib


#endif // __SMALL_H__