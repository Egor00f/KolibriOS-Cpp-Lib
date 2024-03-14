#ifndef __SCREEN_H__
#define __SCREEN_H__


#include <sys/ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/thread.hpp>

namespace KolibriLib
{
	/// @brief Получить разрешение экрана
	/// @return размер экрана
	inline UI::Size GetScreenSize()
	{
		ksys_pos_t a = _ksys_screen_size();
		return UI::Size(a.x, a.y);
	}

	/// @brief Получить принадлежность точки
	/// @param POINT точка на экране
	/// @return слот окна которому принадлежит точка
	inline Thread::Slot ScreenPointAffiliation(UI::Coord POINT)
	{
		Thread::Slot s;
		__asm__ __volatile__(
			"int $0x40"
			: "=a"(s)
			: "a"(34), "b"(POINT.x), "c"(POINT.y)
			);
		return s;
	}

}


#endif // __SCREEN_H__