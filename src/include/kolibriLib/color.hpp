#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>
#include "types.hpp"

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Colors
    {

        /// @brief Цвет
        union Color
        {
            ksys_color_t val;
            struct
            {
                uint8_t a;
                uint8_t red;
                uint8_t green;
                uint8_t blue;

                
            };
            
            Color(ksys_color_t a = 0);

            Color& operator = (const Color& a);

            Color &operator+(const Color &a);

            bool operator == (const Color& a) const;

            bool operator != (const Color& a)const;
        };
        
        /// @brief Смешать 2 цвета
        /// @param a первый цвет
        /// @param b второй цвет
        /// @return Смешение цветов a и b
        Color BlendColors(const Color& a, const Color& b);

        /// @brief Таблица цветов по умолчанию
        const ColorsTable DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


        /// @brief Сравнить две таблица цветов
        /// @param a таблица первая
        /// @param b таблица вторая
        /// @return true если таблицы равны, иначе false
        bool ComparisonColorsTables(const ColorsTable& a, const ColorsTable& b);

        /// @brief Тип данных для работы с argb цветом
        struct ARGB
        {
            uint8_t alpha;
            uint8_t red;
            uint8_t green;
            uint8_t blue;
        };
    }
} // namespace KolibriLib


#endif // __COLOR_H__