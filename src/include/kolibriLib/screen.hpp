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
    UI::Size GetScreenSize();

    /// @brief Получить принадлежность точки
    /// @param POINT точка на экране
    /// @return слот окна которому принадлежит точка
    Thread::Slot ScreenPointAffiliation(UI::Coord POINT);


    /// @brief Получить размеры фонового изображения
    /// @return 
    UI::Size GetBackgroundImageSize();

    /// @brief Прочитать точку на фоне
    /// @param Point читаема точка
    /// @return 
    Colors::Color ReadBackgroungImagePoint(point<unsigned> Point);
}


#endif // __SCREEN_H__