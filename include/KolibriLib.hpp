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
#include <UI.hpp>



namespace KolibriLib
{

	// Тут всё из этой либы используется как KolibriLib::

	using KolibriLib::Colors::Color;
	using KolibriLib::Colors::ColorsTable;

	using KolibriLib::window::Window;

	using filesystem::Path;
	using filesystem::CreateFile;
	using filesystem::MakeDirectory;
	using filesystem::Delete;

	using KolibriLib::OS::Event;
	using KolibriLib::OS::Time;
	using KolibriLib::OS::GetSystemColors;
	using KolibriLib::OS::GetTime;
	using KolibriLib::OS::Exec;
	using KolibriLib::OS::FreeMem;
	using KolibriLib::OS::AllMem;

	using graphic::DrawCircle;
	using graphic::DrawCircleFill;
	using graphic::DrawLine;
	using graphic::DrawPixel;
	using graphic::DrawRectangleFill;
	using graphic::DrawRectangleGradient;
	using graphic::DrawRectangleLines;
	using graphic::DrawTriangle;
	using graphic::ReadArea;
	using graphic::ReadPoint;

	using UI::buttons::DefineButton;
	using UI::buttons::autoDefineButton;
	using UI::buttons::DeleteButton;

} // namespace KolibriLib


#endif // __KOLIBRILIB_H__