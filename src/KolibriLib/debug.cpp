#include <kolibriLib/debug.hpp>
#include <cstdio>

#ifdef DEBUG

#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/filesystem/filesystem.hpp>

#endif



using namespace KolibriLib;



void KolibriLib::DebugOut(const char* out)
{
	#ifdef DEBUG
	_ksys_debug_puts(out);

	std::ofstream debugOut(filesystem::temp_directory_path() / std::string(Thread::GetThreadInfo().name + "-debug.log"), std::ios::app);

	if(debugOut.is_open())
	{
		debugOut << out;
	}
	else
	{
		_ksys_debug_puts("\ncan't open log file\n");
	}

	debugOut.close();

	#endif
}

void KolibriLib::PrintDebug(bool out)
{
	if(out)
	{
		DebugOut("true");
	}
	else
	{
		DebugOut("false");
	}
}

void KolibriLib::PrintDebug(const std::string &out)
{
	DebugOut(out.c_str());
}

void KolibriLib::PrintDebug(const char* out)
{
	DebugOut(out);
}

void KolibriLib::PrintDebug(int out)
{
	char buff[8];
	std::sprintf(buff, "%i", out);
	DebugOut(buff);
}

void KolibriLib::PrintDebug(unsigned out)
{
	char buff[8];
	std::sprintf(buff, "%u", out);
	DebugOut(buff);
}

void KolibriLib::PrintDebug(float out)
{
	char buff[10];
	std::sprintf(buff, "%f", out);
	DebugOut(buff);
}