#include <kolibriLib/debug.hpp>

using namespace KolibriLib;

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

void KolibriLib::PrintDebug(char out)
{
	#ifdef DEBUG
	_ksys_debug_putc(out);
	#endif
}

void KolibriLib::PrintDebug(std::string out)
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
	sprintf(buff, "%i", out);
	DebugOut(buff);
}

void KolibriLib::PrintDebug(unsigned out)
{
	char buff[8];
	sprintf(buff, "%u", out);
	DebugOut(buff);
}

void KolibriLib::PrintDebug(float out)
{
	char buff[10];
	sprintf(buff, "%f", out);
	DebugOut(buff);
}