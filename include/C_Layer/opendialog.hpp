#ifndef __C_LAYER_OPENDIALOG_HPP__
#define __C_LAYER_OPENDIALOG_HPP__

#include <C_Layer/INCLUDE/kolibri_opendialog.h>

#ifndef __MakeStaticLib__

class proclibLib
{
public:
	proclibLib()
	{
		kolibri_proclib_init();
	}
};

proclibLib proclibLibv;

#endif

#endif // __OPENDIALOG_HPP__