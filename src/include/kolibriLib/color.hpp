#ifndef __COLOR_H__
#define __COLOR_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    /// @brief Набор функций для работы с цветом
    namespace Color
    {
        /// @brief Таблица цветов по умолчанию
        const ksys_colors_table_t DefaultColorTable = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /// @brief Сравнить две таблица цветов
        /// @param a таблица первая
        /// @param b таблица вторая
        /// @return true если таблицы равны, иначе false
        bool ComparisonColorsTables(ksys_colors_table_t a, ksys_colors_table_t b)
        {
            if (a.frame_area == b.frame_area && a.grab_bar == b.grab_bar && a.grab_bar_button == a.grab_bar_button && a.grab_button_text == b.grab_button_text && a.grab_text == b.grab_text && a.work_area == b.work_area && a.work_button == b.work_button)
            {
                return true;
            }
            return false;
        }

        template <class ImageBits>
        /// @brief Битность цвета. Варианты <ImageBits>:
        /// @brief uint8_t, для 8bit,
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