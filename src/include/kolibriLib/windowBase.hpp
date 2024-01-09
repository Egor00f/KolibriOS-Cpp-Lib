#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__


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
            if(a.frame_area == b.frame_area && a.grab_bar == b.grab_bar && a.grab_bar_button == a.grab_bar_button && a.grab_button_text == b.grab_button_text && a.grab_text == b.grab_text && a.work_area == b.work_area && a.work_button == b.work_button)
            {
                return true;
            }
            return false;
        }
    }

    /// @brief Работа с окном
    namespace window
    {


        /// @brief Размер окна поумолчанию
        const point DefaultWindowSize = {400, 400};

        /// @brief Соординаты окна по умолчанию
        const point DefaultWindowCoord = {100, 100};



        /// @brief Снять фокус с окна
        /// @param slot слот окна
        inline void UnfocusWindow(int slot)
        {
            _ksys_unfocus_window(slot);
        }
        /// @brief Поставить фокус на окно
        /// @param slot слот окна
        inline void FocusWindow(int slot)
        {
            _ksys_focus_window(slot);
        }

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__