#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/UI/buttonsBase.hpp>

namespace KolibriLib
{
	/// @brief Список глобальных переменных
	namespace Globals
	{
		Colors::ColorsTable SystemColors = OS::GetSystemColors();

		UI::buttons::ButtonsIDController *DefaultButtonsIDController = nullptr;
	} // namespace Globals
	
} // namespace KolibriLib


#endif // __GLOBALS_H__