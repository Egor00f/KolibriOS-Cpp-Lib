#ifndef __KOLIBRILIB_HPP__
#define __KOLIBRILIB_HPP__

#include <kolibriLib/window/window.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/system/filesystem/filesystem.hpp>
#include <kolibriLib/childWindow.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/graphic/background.hpp>
#include <kolibriLib/network.hpp>
#include <kolibriLib/OpenDialog.hpp>
#include <kolibriLib/input/clipboard.hpp>
#include <input.hpp>
#include <KolibriLibUI.hpp>


/// @brief Прастранство имён библиотеки KolibriLib
/// @author Egor00f
namespace KolibriLib
{

	// Тут всё из этой либы используется как KolibriLib::

	using KolibriLib::Colors::Color;
	using KolibriLib::Colors::ColorsTable;

	using KolibriLib::window::Window;

	using filesystem::Path;

	using KolibriLib::OS::Event;
	using KolibriLib::OS::GetSystemColors;
	using KolibriLib::OS::Exec;
	using KolibriLib::OS::GetFreeMem;
	using KolibriLib::OS::AllMem;
	using KolibriLib::OS::SetEventMask;
	using KolibriLib::OS::GetEventMask;

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

	using mouse::GetMousePositionOnSreen;
	using mouse::GetMousePositionInWindow;
	using mouse::GetMouseEvents;
	using mouse::GetMouseButtons;
	using mouse::CenterCursor;

} // namespace KolibriLib


#endif // __KOLIBRILIB_HPP__