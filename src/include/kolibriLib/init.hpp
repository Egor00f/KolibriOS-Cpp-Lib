#pragma once

#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>


#include <kolibri_gui.h>

#include <kolibri_libimg.h>

#include <sound.h>

#include "filesystem.hpp"
#include "os.hpp"
#include "thread.hpp"

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{

    /// @brief инициализация
    void init()
    {
        OS::GetSystemColors();
        if(kolibri_gui_init() != 0)
        {
            _ksys_debug_puts("Error loading kolibri_gui.h, exit\n");
            exit(0);
        }

        if(kolibri_libimg_init() != 0)
        {
            _ksys_debug_puts("Error loading lib_img.obj, exit\n");
            exit(0);
        }

        /*if ( int version = -1; !InitSound(&version))
        {
            _ksys_debug_puts("Error loading sound.h, exit\n");
            exit(0);
        }*/

        


        _ksys_set_event_mask(0x07);
    
        
    }
}



#endif // __BASE_H__