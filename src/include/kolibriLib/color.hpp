#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Color
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
        };
        
        /// @brief Смешать 2 цвета
        /// @param a первый цвет
        /// @param b второй цвет
        /// @return Смешение цветов a и b
        Color BlendColors(const Color& a, const Color& b)
        {
            Color result;
            result.red      = (a.red + b.red) / 2;   //Среднее арифметическое
            result.green    = (a.green + b.green) / 2;
            result.blue     = (a.blue + b.blue) / 2;
            return result;
        }

        /// @brief Таблица цветов
        typedef ksys_colors_table_t ColorsTable;

        /// @brief Таблица цветов по умолчанию
        const ColorsTable DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


        /// @brief Сравнить две таблица цветов
        /// @param a таблица первая
        /// @param b таблица вторая
        /// @return true если таблицы равны, иначе false
        bool ComparisonColorsTables(const ColorsTable& a, const ColorsTable& b)
        {
            if (a.frame_area == b.frame_area && a.grab_bar == b.grab_bar && a.grab_bar_button == a.grab_bar_button && a.grab_button_text == b.grab_button_text && a.grab_text == b.grab_text && a.work_area == b.work_area && a.work_button == b.work_button)
            {
                return true;
            }
            return false;
        }

        template <class ImageBits>
        /// @brief Тип данных для работы с argb цветом
        /// @paragraph Варианты <ImageBits>:
        /// @paragraph uint8_t, для 8bit,
        /// @paragraph uint16_t для 16,
        /// @paragraph uint32_t,
        /// @paragraph uint64_t,
        struct ARGB_t
        {
            ImageBits alpha;
            ImageBits red;
            ImageBits green;
            ImageBits blue;
        };
    }
} // namespace KolibriLib


#endif // __COLOR_H__