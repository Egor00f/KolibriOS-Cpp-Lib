#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>
#include "types.hpp"

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Colors
    {
        /// @brief Тип данных для работы с argb цветом
        struct ARGB
        {
            uint8_t alpha;
            uint8_t red;
            uint8_t green;
            uint8_t blue;
        };
        
        /// @brief Цвет
        union Color
        {
            ksys_color_t val;
            struct
            {
                uint8_t _a;
                uint8_t red;
                uint8_t green;
                uint8_t blue;

                
            };
            
            /// @brief Конструктор
            /// @param a 
            Color(ksys_color_t a = 0);
            Color(const Color &a);
            Color(const ARGB &a);

            Color& operator = (const Color& a);

            Color &operator+(const Color &a);

            bool operator == (const Color& a) const;

            bool operator != (const Color& a)const;
        };
        

        /// @brief Таблица цветов по умолчанию
        const ksys_colors_table_t DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /// @brief Таблица цветов
        struct ColorsTable : public ksys_colors_table_t
        {
            ColorsTable(ksys_colors_table_t table = DefaultColorTable);
            
            bool operator == (const ColorsTable &table) const;
            bool operator != (const ColorsTable &table) const;
        };

        
        
    }
} // namespace KolibriLib


#endif // __COLOR_H__