#include <C_Layer/libimg.hpp>
#include <kolibriLib/debug.hpp>

libimgLib libimgLibv;

libimgLib::libimgLib()
{
	KolibriLib::PrintDebug("Init libimg: ");
	int err = kolibri_libimg_init();
	if (err == -1)
	{
		KolibriLib::PrintDebug("Error\n");
		throw err;
	}
	else
	{
		KolibriLib::PrintDebug("OK\n");
	}
}