#ifndef __SCREEN_H__
#define __SCREEN_H__


#include <sys/ksys.h>

#include "small.hpp"
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
}


#endif // __SCREEN_H__