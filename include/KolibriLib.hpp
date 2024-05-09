#ifndef __KOLIBRILIB_H__
#define __KOLIBRILIB_H__

#include <kolibriLib/init.hpp>
#include <kolibriLib/window/window.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/childWindow.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/graphic/background.hpp>
#include <kolibriLib/network.hpp>
#include <input.hpp>
#include <kolibriLib/libini.hpp>
#include <UI.hpp>

namespace KolibriLib
{
	using KolibriLib::Colors::Color;
	using KolibriLib::window::Window;
	using filesystem::Path;


	using KolibriLib::OS::GetSystemColors;
	using KolibriLib::OS::Event;

} // namespace KolibriLib


#endif // __KOLIBRILIB_H__