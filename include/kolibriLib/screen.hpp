#pragma once
#ifndef __SCREEN_H__
#define __SCREEN_H__

extern "C"
{
    #include <sys/ksys.h>
}
#include "base.hpp"

namespace KolibriLib
{
    /// @brief Получить разрешение экрана
    /// @return размер экрана
    point GetScreenSize()
    {
        ksys_pos_t a = _ksys_screen_size();
        return {a.x, a.y};
    }
}


#endif // __SCREEN_H__