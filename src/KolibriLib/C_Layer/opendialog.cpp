#include <C_Layer/opendialog.hpp>
#include <kolibriLib/debug.hpp>

proclibLib proclibLibv;

proclibLib::proclibLib()
{
	KolibriLib::logger << microlog::LogLevel::Debug << "Init proclib: ";
	kolibri_proclib_init();
	KolibriLib::logger << "OK" << std::endl;
}