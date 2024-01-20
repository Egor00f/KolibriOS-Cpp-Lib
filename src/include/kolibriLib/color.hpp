#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Color
    {

        /// @brief Цвет
        typedef ksys_color_t Color;

        /// @brief Таблица цветов
        typedef ksys_colors_table_t ColorsTable;

        /// @brief Таблица цветов по умолчанию
        const ColorsTable DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


        /// @brief Сравнить две таблица цветов
        /// @param a таблица первая
        /// @param b таблица вторая
        /// @return true если таблицы равны, иначе false
        bool ComparisonColorsTables(ColorsTable a, ColorsTable b)
        {
            if (a.frame_area == b.frame_area && a.grab_bar == b.grab_bar && a.grab_bar_button == a.grab_bar_button && a.grab_button_text == b.grab_button_text && a.grab_text == b.grab_text && a.work_area == b.work_area && a.work_button == b.work_button)
            {
                return true;
            }
            return false;
        }

        template <class ImageBits>
        /// @brief Битность цвета. 
        /// @paragraph Варианты <ImageBits>:
        /// @ uint8_t, для 8bit,
        /// @brief uint16_t для 16,
        /// @brief uint32_t,
        /// @brief uint64_t,
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