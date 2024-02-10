#pragma once

#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>

extern "C"
{
#include <kolibri_libimg.h>
}
#include <sound.h>

#include "filesystem.hpp"
#include "os.hpp"

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{

    /// @brief инициализация
    void init()
    {
        if(kolibri_libimg_init() == -1)
        {
            _ksys_debug_puts("Error loading lib_img.obj, exit\n");
            exit(0);
        }

        if ( int version = -1; !InitSound(&version))
        {
            _ksys_debug_puts("Erroe loading sound.h, exit");
        }

            _ksys_set_event_mask(0x07);
        OS::GetSystemColors();
    }
}



#endif // __BASE_H__