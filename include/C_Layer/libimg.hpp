#ifndef __LIBIMG_H__
#define __LIBIMG_H__

#include <C_Layer/INCLUDE/kolibri_libimg.h>

#ifndef __MakeStaticLib__
class libimgLib
{
public:
	libimgLib()
	{
		if(kolibri_libimg_init() == -1)
			throw;
	}
};

libimgLib libimgLibv;
#endif

#endif // __LIBIMG_H__