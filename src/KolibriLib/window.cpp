#include <kolibriLib/window/window.hpp>

using namespace KolibriLib;
using namespace window;

KolibriLib::window::Window::Window(const std::string &Title, const KolibriLib::Size &size, const KolibriLib::Colors::ColorsTable &colors, bool Resize, bool RealtimeRedraw, bool Gradient, unsigned Transparency, Pos position, const unsigned &Margin)
	: _title(Title),
	  _colors(colors),
	  _Transparency(Transparency),
	  _RealtimeRedraw(RealtimeRedraw)
{
	_style = 0;
	_style = WindowStyle::Relative | WindowStyle::WindowHaveTitle | WindowStyle::withSkin;

	if (Resize)
	{
		_style |= WindowStyle::CanResize;
	}
	else
	{
		_style |= WindowStyle::FixSize;
	}

	if (Gradient)
	{
		_style |= WindowStyle::GradientDraw;
	}

	/* if (_Transparency > 0)
	{
		_style |= WindowStyle::NoDrawWorkspace;
	} */

	SetMargin(Margin);

	window::CreateWindow (
		DefaultWindowCoord,
		size,
		_title,
		_colors.work_area,
		_colors.grab_text,
		_style);

	SetPosition(position);

	if(Globals::DefaultButtonsIDController == nullptr)
	{
		Globals::DefaultButtonsIDController = &_buttonsController;
	}
}

KolibriLib::window::Window::~Window()
{
	for (auto n : _Elements)
	{
		if (!(n == nullptr))
		{
			delete n;
		}
	}
}

void Window::RenderAllElements() const
{
	#ifdef DEBUG
	_ksys_debug_puts("RenderAllElements:");
	#endif

	for (auto i : _Elements)
	{
		i->Render();
	}

	#ifdef DEBUG
	_ksys_debug_puts("done\n");
	#endif
}

void Window::SetWindowColors(const Colors::ColorsTable &colorTable)
{
	_colors = colorTable;
}

void Window::StartRedraw() const
{
	_ksys_start_draw();
	_Redraw = true;
}

void Window::EndRedraw() const
{
	if (_Redraw)
	{
		_ksys_end_draw();
		_Redraw = false;
	}
}

UDim KolibriLib::window::Window::GetCoord() const
{
	return window::GetWindowCoord();
}

inline void Window::SetCoord(const UDim &NewCoord)
{
	ChangeWindow(NewCoord.GetAbsolute(GetScreenSize()), GetAbsoluteSize());
}

inline void Window::SetSize(const Size &NewSize)
{
	ChangeWindow(GetAbsoluteCoord(), NewSize);
}

inline void Window::SetCoord(const Coord &NewCoord)
{
	ChangeWindow(NewCoord, GetAbsoluteSize());
}

inline void Window::SetSize(const UDim &NewSize)
{
	ChangeWindow(GetAbsoluteCoord(), NewSize.GetAbsolute(GetScreenSize()));
}

inline Coord Window::GetAbsoluteCoord() const
{
	return window::GetWindowCoord();
}

inline Size Window::GetAbsoluteSize() const
{
	return window::GetWindowSize();
}

void Window::ChangeWindow(const Coord &coord, const Size &size)
{
	_ksys_change_window(coord.x, coord.y, size.x, size.y);
}

void Window::ChangeTilte(const std::string &newTitle)
{
	_ksys_set_window_title(newTitle.c_str());
}

void KolibriLib::window::Window::Redraw()
{
	#ifdef DEBUG
	_ksys_debug_puts("Redraw");
	#endif

	StartRedraw();
	window::CreateWindow(GetAbsoluteCoord(), {0, 0}, _title, _colors.work_area, _colors.grab_text, _style);

	/*if (_style & window::WindowStyle::CanResize)
	{
		static Size LastWindowSize;

		if (window::GetWindowSize() == LastWindowSize)
		{
			LastWindowSize = window::GetWindowSize();

			for (auto n : _Elements)
			{
				if (n->RenderOnEverythingRedraw)
				{
					n->Render();
				}
			}
		}
	}
	else
	{
		for (auto n : _Elements)
		{
			if (n->RenderOnEverythingRedraw)
			{
				n->Render();
			}
		}
	}*/

	RenderAllElements();

	/*if (_Transparency != 0) // Прозрачность окна
	{
		// for (int i = 0; i < _size.y; i++)
		//{
		//	for (int j = 0; j < _size.x; j++)
		//	{
		//		graphic::DrawPixel({j, i}, Colors::BlendColors(graphic::ReadPoint({j, i}), Background::ReadPoint({j, i}), 100 / _Transparency)); // Пока так, потом может быть станет лучше
		//	}
		// }
	}*/

	EndRedraw();

	#ifdef DEBUG
	_ksys_debug_puts("done\n");
	#endif
}

void Window::Render()
{
	PrintDebug("Render window:");

	StartRedraw();
	window::CreateWindow({0, 0}, {0, 0}, _title, _colors.work_area, _colors.grab_text, _style);

	KolibriLib::graphic::DrawRectangleFill({0, (int)window::GetSkinHeight()}, GetWindowSize(), Colors::UINT32toRGB(_colors.work_area));

	RenderAllElements();

	/* if (_Transparency != 0) // Прозрачность окна
	{
		Size size = GetWindowSize();
		for (int i = 0; i < size.y; i++)
		{
			for (int j = 0; j < size.x; j++)
			{
				graphic::DrawPixel({j, i}, Colors::BlendColors(graphic::ReadPoint({j, i}), Background::ReadPoint({j, i}), 100 / _Transparency));
			}
		}
	} */

	EndRedraw();

	#ifdef DEBUG
	_ksys_debug_puts("done\n");
	#endif
}

inline UDim Window::GetSize() const
{
	Size p = GetAbsoluteSize();
	return UDim(0, p.x, 0, p.y);
}

OS::Event Window::Handler()
{
#ifdef DEBUG
	_ksys_debug_puts("Handler\n");
#endif

	OS::Event event = OS::WaitEvent();

	switch (event)
	{
	case OS::Events::Redraw:

		Redraw();

		break;
	case OS::Events::Button:

		if (UI::buttons::GetPressedButton() == 1) // Если нажата кнопка X
		{
			return OS::Events::Exit;
		}

		for (auto it : _Elements) // Запуск обработчиков всех используемых элементов
		{
			it->Handler();
		}

		break;
	case OS::Events::Key:

		for (auto it : _Elements)
		{
			it->Handler();
		}

		break;
	case OS::Events::Mouse:

		if (mouse::MouseButtons::RightButton && mouse::MouseButtons()) // Если нажата правая кнопка
		{
			Coord m = mouse::GetMousePositionInWindow();

			if (m.x < GetSize().GetAbsolute().x && m.y < window::GetSkinHeight())
			{
			}
		}

		break;
	}

	if (_RealtimeRedraw)
	{
		Coord Mouse = mouse::GetMousePositionInWindow();
		if ( ((Mouse.x > 0 && Mouse.y > 0)	&& 
		       Mouse.x < GetWindowSize().x	&& 
			   Mouse.y < GetSkinHeight())	&& 
			   mouse::GetMouseButtons() == mouse::LeftButton)
		{
			while (mouse::GetMouseButtons() == mouse::LeftButton)
			{
				_ksys_thread_yield();
			}
		}
	}

	return event;
}

UI::buttons::ButtonID Window::GetPressedButton()
{
	for (auto &n : _Elements)
	{
		if (n->ClassName == "Button")
		{
			if (((UI::buttons::Button *)n)->GetStatus())
			{
				return ((UI::buttons::Button *)n)->GetId();
			}
		}
	}

	return UI::buttons::ButtonIDNotSet;
}

void KolibriLib::window::Window::Unfocus() const
{
	_ksys_unfocus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
}

void KolibriLib::window::Window::Focus() const
{
	_ksys_focus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
}

void KolibriLib::window::Window::SetPosition(const window::Pos &position)
{
	window::SetWindowPos(position);
}

window::Pos KolibriLib::window::Window::GetPosition() const
{
	return window::GetWindowPos();
}

UI::buttons::ButtonsIDController *KolibriLib::window::Window::GetButtonIDController() const
{
	return (UI::buttons::ButtonsIDController *)&_buttonsController;
}

void KolibriLib::window::Window::SetButtonIDController(const UI::buttons::ButtonsIDController* buttonsIDController) 
{
	
}