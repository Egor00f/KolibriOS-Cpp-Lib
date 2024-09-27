#include <C_Layer/buf2d.hpp>
#include <kolibriLib/debug.hpp>

buf2dLib buf2dLibv;

buf2dLib::buf2dLib()
{
	KolibriLib::PrintDebug("Init buf2d: ");

	int err = kolibri_buf2d_init();

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