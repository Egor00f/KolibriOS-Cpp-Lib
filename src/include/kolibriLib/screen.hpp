#ifndef __SCREEN_H__
#define __SCREEN_H__


#include <sys/ksys.h>

#include "small.hpp"

namespace KolibriLib
{
    /// @brief Получить разрешение экрана
    /// @return размер экрана
    point<unsigned> GetScreenSize()
    {
        ksys_pos_t a = _ksys_screen_size();
        return (point<unsigned>){a.x, a.y};
    }


}


#endif // __SCREEN_H__