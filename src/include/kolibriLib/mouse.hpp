#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <sys/ksys.h>
#include "small.hpp"

namespace KolibriLib
{
    /// @brief Работа с мышью
    namespace mouse
    {

        /// @brief Получить позицияю курсора на экране
        /// @return (point) позиция курсора абсолютно
        inline point<int> GetMousePositionOnSreen();

        /// @brief Получить позицияю курсора внутри окна
        /// @return (point) позиция курсора относительно окна
        inline point<int> GetMousePositionInWindow();

        /// @brief Проверить какие кнопки мыши нажаты
        /// @return
        inline uint32_t GetMouseButtons();

        /// @brief колёсико мыши
        /// @return
        inline uint32_t GetMouseWheels();

    }
} // namespace KolibriLib


#endif // __MOUSE_H__