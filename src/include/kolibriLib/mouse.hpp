#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <sys/ksys.h>
#include "base.hpp"
#include "UI.hpp"

namespace KolibriLib
{
    /// @brief Работа с мышью
    namespace mouse
    {
        /// @brief Получить позицияю курсора на экране
        /// @return (point) позиция курсора
        inline point<int> GetMousePositionOnSreen()
        {
            ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_SCREEN_POS);

            return {a.x, a.y};
        }

        /// @brief Получить позицияю курсора внутри окна
        /// @return (point) позиция курсора
        inline UI::Coord GetMousePositionInWindow()
        {
            ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS);

            return (UI::Coord){a.x, a.y};
        }

        /// @brief Проверить какие кнопки мыши нажаты
        /// @return 
        inline uint32_t GetMouseButtons()
        {
            return _ksys_get_mouse_buttons();
        }

        /// @brief колёсико мыши
        /// @return 
        inline uint32_t GetMouseWheels()
        {
            return _ksys_get_mouse_wheels();
        }

    }
}


#endif // __MOUSE_H__