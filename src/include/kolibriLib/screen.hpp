#ifndef __SCREEN_H__
#define __SCREEN_H__


#include <sys/ksys.h>

#include "types.hpp"
#include "color.hpp"
#include "thread.hpp"

namespace KolibriLib
{
    /// @brief Получить разрешение экрана
    /// @return размер экрана
    point<unsigned> GetScreenSize();

    /// @brief Получить принадлежность 
    /// @param POINT 
    /// @return 
    Thread::Slot ScreenPointAffiliation(point<unsigned> POINT);

    /// @brief Центрировать курсор
    inline void CenterCursor();

    /// @brief Получить размеры фонового изображения
    /// @return 
    point<unsigned> GetBackgroundImageSize();

    /// @brief Прочитать точку на фоне
    /// @param Point читаема точка
    /// @return 
    Colors::Color ReadBackgroungImagePoint(point<unsigned> Point);
}


#endif // __SCREEN_H__