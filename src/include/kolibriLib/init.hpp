#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>

#include <kolibri_libimg.h>

#include <sound.h>

#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/system/thread.hpp>

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{

    /// @brief инициализация
    void init()
    {
        OS::GetSystemColors();

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