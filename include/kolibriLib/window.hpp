#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>


#include <sys/ksys.h>

#include "base.hpp"
#include "mouse.hpp"
#include "windowBase.hpp"
#include "UI.hpp"

namespace KolibriLib
{ //=============================================================================================================================================================

	

	// Работа с окном
	namespace window
	{


		// @brief Создать окно
		void initWindow()
		{
			_ksys_set_event_mask(0x07);
			_ksys_debug_puts("Window");
			OS::GetSystemColors();
			SetWindowColors(OS::sys_color_table);
			DrawWindow(DefaultWindowCoord, DefaultWindowSize, "Window");
		}

		
	}

	//=============================================================================================================================================================

	

}




//=============================================================================================================================================================


#endif