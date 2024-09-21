#include <kolibriLib/debug.hpp>
#include <cstdio>

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