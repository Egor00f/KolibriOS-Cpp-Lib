#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__

extern "C"
{
    #include <sys/ksys.h>
}


namespace KolibriLib
{
    /// @brief Работа с окном
    namespace window
    {
        ksys_colors_table_t colors;

        /// @brief отступы от края окна
        unsigned MARGIN = 0;

        /// @brief Окно перерисовывается сейчас (да/нет)
        bool Redraw = false;

        /// @brief Размер окна поумолчанию
        const point DefaultWindowSize = {400, 400};

        /// @brief Соординаты окна по умолчанию
        const point DefaultWindowCoord = {100, 100};

        /// @brief Задать стандартные цвета окна
        /// @param colorTable таблица цветов
        void SetWindowColors(ksys_colors_table_t colorTable)
        {
            colors = colorTable;
        }

        /// @brief Начать перересовку окна
        /// @paragraph Стирает всё что было нарисованно в окне
        /// @paragraph Обязательно после должна быть вызвана функция #EndRedraw()
        inline void StartRedraw()
        {
            _ksys_start_draw();
            Redraw = true;
        }

        /// @brief Закончить перересовку окна
        /// @paragraph Обязательно после должна быть вызвана функция #StartRedraw()
        inline void EndRedraw()
        {
            _ksys_end_draw();
            Redraw = false;
        }

        /// @brief Отрисовать окно
        /// @param coord позиция окна
        /// @param size размер окна
        /// @param title титул(текст в заголовке)
        /// @param color цвет рабочей области
        /// @param style стиль
        void DrawWindow(point coord = DefaultWindowCoord, point size = DefaultWindowSize, std::string title = "Window", int style = 0x13, ksys_color_t color = colors.work_area, unsigned margin = 0)
        {
            MARGIN = margin;
            colors.work_area = color;
            _ksys_create_window(coord.x, coord.y, size.x, size.y, title.c_str(), color, style);
        }

        /// @brief Отрисовать окно
        /// @param coord позиция окна
        /// @param size размер окна
        /// @param title титул(текст в заголовке)
        /// @param color цвет рабочей области
        /// @param style стиль
        void DrawWindow(point coord = DefaultWindowCoord, point size = DefaultWindowSize, const char *title = "Window", int style = 0x13, ksys_color_t color = colors.work_area, unsigned margin = 0)
        {
            MARGIN = margin;
            colors.work_area = color;
            _ksys_create_window(coord.x, coord.y, size.x, size.y, title, color, style);
        }

        /// @brief Изменить окно
        /// @param coord позиция
        /// @param size размер
        inline void ChangeWindow(point coord, point size)
        {
            _ksys_change_window(coord.x, coord.y, size.x, size.y);
        }

        /// @brief Изменить заголовок окна
        /// @param newTitle новый заголовок
        inline void ChangeTilte(std::string newTitle)
        {
            _ksys_set_window_title(newTitle.c_str());
        }

        /// @brief Получить размер окна
        /// @return point.x - ширина окна,
        /// @return point.y - высота окна
        point GetWindowSize()
        {
            ksys_thread_t *t;
            _ksys_thread_info(t, -1);
            return {t->winx_size, t->winy_size};
        }

        /// @brief Снять фокус с окна
        /// @param slot
        inline void UnfocusWindow(int slot)
        {
            _ksys_unfocus_window(slot);
        }
        /// @brief
        /// @param slot
        inline void FocusWindow(int slot)
        {
            _ksys_focus_window(slot);
        }

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__