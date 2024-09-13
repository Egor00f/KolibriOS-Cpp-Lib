#ifndef __BUF2D_HPP__
#define __BUF2D_HPP__

#include <C_Layer/INCLUDE/kolibri_buf2d.h>

#ifndef __MakeStaticLib__

class buf2dLib
{
public:
	buf2dLib()
	{
		if(kolibri_buf2d_init() == -1)
			throw;
	}
};

buf2dLib buf2dLibv;

#endif

#endif // __BUF2D_H__