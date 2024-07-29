

#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <sys/ksys.h>
#include <stdio.h>
#include <string>

namespace KolibriLib
{
	inline void DebugOut(const char* out)
	{
		#ifdef DEBUG
		_ksys_debug_puts(out);
		#endif
	}


	void PrintDebug(char out);

	void PrintDebug(std::string out);

	void PrintDebug(const char* out);

	void PrintDebug(int out);

	void PrintDebug(unsigned out);

	void PrintDebug(float out);

} // namespace KolibriLib


#endif // __DEBUG_H__
