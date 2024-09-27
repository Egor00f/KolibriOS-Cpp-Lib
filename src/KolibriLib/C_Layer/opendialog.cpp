#include <C_Layer/opendialog.hpp>
#include <kolibriLib/debug.hpp>

proclibLib proclibLibv;

proclibLib::proclibLib()
{
	KolibriLib::PrintDebug("Init proclib: ");
	kolibri_proclib_init();
	KolibriLib::PrintDebug("OK\n");
}