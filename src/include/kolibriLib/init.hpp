#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>

#include <kolibri_libimg.h>
#include <kolibri_rasterworks.h>
#include <kolibri_libini.h>

//#include <sound.h>

#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/system/thread.hpp>

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{

	/// @brief инициализация библиотеки
	inline void init()
	{
		OS::GetSystemColors();

		if(kolibri_libimg_init() != -1)
		{
			_ksys_debug_puts("Error loading lib_img.obj, exit\n");
			exit(0);
		}

		/*if ( int version = -1; !InitSound(&version))
		{
			_ksys_debug_puts("Error loading sound.h, exit\n");
			exit(0);
		}*/

		kolibri_libini_init();
		kolibri_rasterworks_init();
		


		_ksys_set_event_mask(0xC0000027);
	
		
	}
}



#endif // __BASE_H__