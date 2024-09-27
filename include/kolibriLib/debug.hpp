#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <include_ksys.h>
#include <string>

namespace KolibriLib
{
	void DebugOut(const char* out);

	void PrintDebug(bool out);

	void PrintDebug(const std::string &out);

	void PrintDebug(const char* out);

	void PrintDebug(int out);

	void PrintDebug(unsigned out);

	void PrintDebug(float out);

} // namespace KolibriLib


#endif // __DEBUG_HPP__
