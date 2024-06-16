#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>

#include <C_Layer/INCLUDE/kolibri_libimg.h>
#include <C_Layer/INCLUDE/kolibri_rasterworks.h>
#include <C_Layer/INCLUDE/kolibri_buf2d.h>

//#include <sound.h>

#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/globals.hpp>
//#include <kolibriLib/UI/text/freetypefuncs.hpp>

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{

	/// @brief инициализация библиотеки
	inline void init()
	{
		
		if(kolibri_libimg_init() == -1)
		{
			_ksys_debug_puts("Error loading libimg.obj, exit\n");
			OS::ErrorNotify("Error loading libimg", "exit");
			exit(0);
		}

		//if ( int version = -1; !InitSound(&version))
		//{
		//	_ksys_debug_puts("Error loading sound.h, exit\n");
		//	exit(0);
		//}
		
		if(kolibri_rasterworks_init() == -1)
		{
			_ksys_debug_puts("Error loading lib RasterWorks, exit\n");
			OS::ErrorNotify("Error loading lib RasterWorks", "exit");
			exit(0);
		}

		if(kolibri_buf2d_init() == -1)
		{
			_ksys_debug_puts("Error loading RasterWorks, exit\n");
			OS::ErrorNotify("Error loading lib buf2d", "exit");
			exit(0);
		}

		
		
	}
}



#endif // __BASE_H__