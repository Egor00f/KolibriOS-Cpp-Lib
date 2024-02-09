#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>

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
            
            Color(ksys_color_t a = 0)
            {
                val = a;
            }

            Color& operator = (const Color& a)
            {
                val = a.val;
                return *this;
            }
            bool operator == (const Color& a) const
            {
                return val == a.val;
            }
            bool operator != (const Color& a)const
            {
                return val != a.val;
            }
        };
        
        /// @brief Смешать 2 цвета
        /// @param a первый цвет
        /// @param b второй цвет
        /// @return Смешение цветов a и b
        Color BlendColors(const Color& a, const Color& b);

        /// @brief Таблица цветов
        typedef ksys_colors_table_t ColorsTable;

        /// @brief Таблица цветов по умолчанию
        const ColorsTable DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


        /// @brief Сравнить две таблица цветов
        /// @param a таблица первая
        /// @param b таблица вторая
        /// @return true если таблицы равны, иначе false
        bool ComparisonColorsTables(const ColorsTable& a, const ColorsTable& b);

        template <class ImageBits>
        /// @brief Тип данных для работы с argb цветом
        /// @paragraph Варианты <ImageBits>:
        /// @paragraph uint8_t, для 8bit,
        /// @paragraph uint16_t для 16,
        /// @paragraph uint32_t,
        /// @paragraph uint64_t,
        struct ARGB
        {
            ImageBits alpha;
            ImageBits red;
            ImageBits green;
            ImageBits blue;
        };
    }
} // namespace KolibriLib


#endif // __COLOR_H__