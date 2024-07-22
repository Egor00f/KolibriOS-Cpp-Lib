#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <sys/ksys.h>

#include <stdlib.h>
#include <string>
#include <utility>
#include <algorithm>


#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <input.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <UI.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/graphic/background.hpp>

namespace KolibriLib
{

	/// \brief Работа с окном
	namespace window
	{

		/// @brief Класс для работы с окном
		/// @paragraph По простому: Окно остаётся привязаным к потоку, в которм бы вызван конструктор
		/// @paragraph Для тех кто знает:
		class Window: public UI::GuiObject
		{
		public:

			std::string ClassName = "Window";

			/// @brief Конструктор
			/// @param Title Заголовок окна
			/// @param size Размер окна
			/// @param style стиль окна
			/// @param colors Цвет окна
			/// @param Margin Отступы
			Window(const std::string &Title = "Window", const Size &size = DefaultWindowSize, const Colors::ColorsTable &colors = OS::GetSystemColors(), bool Resize = false, bool RealtimeReadraw = false, bool Gradient = false, unsigned Transparency = 0, const unsigned &Margin = 0);

			~Window();

			/// @brief Полная перересовка окна
			void Redraw();

			/// @brief Отрисовать окно
			void Render(const Coord &coord = DefaultWindowCoord);

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin() const;

			/// @brief Получить размер окна
			/// @return _size
			UI::UDim GetSize() const override;

			/// @brief Получить координаты окна
			/// @return
			UI::UDim GetCoord() const override;

			void SetSize(const UDim &NewSize) override;

			/// @brief 
			/// @param NewCoord 
			void SetCoord(const UDim &NewCoord) override;

			void SetSize(const Size &NewSize) override;

			/// @brief 
			/// @param NewCoord 
			void SetCoord(const Coord &NewCoord) override;

			/// @brief 
			/// @return 
			Coord GetAbsoluteCoord() const override;

			/// @brief 
			/// @return 
			Size GetAbsoluteSize() const override;

			/// @brief Задать стандартные цвета окна
			/// @param colorTable таблица цветов
			void SetWindowColors(const Colors::ColorsTable &colorTable);

			/// @brief Начать перересовку окна
			/// @note Стирает всё что было нарисованно в окне
			/// @note Обязательно после должна быть вызвана функция #EndRedraw()
			void StartRedraw() const;

			/// @brief Закончить перересовку окна
			/// @note Обязательно после должна быть вызвана функция #StartRedraw()
			void EndRedraw() const;

			/// @brief Изменить окно
			/// @param coord позиция
			/// @param size размер
			void ChangeWindow(const Coord &coord, const Size &size);

			/// @brief Изменить заголовок окна
			/// @param newTitle новый заголовок
			void ChangeTilte(const std::string &newTitle);

			/// @brief Обработчик окна
			/// @return Ивент
			OS::Event Handler();

			/// @brief Проверить какая нажата
			UI::buttons::ButtonID GetPressedButton();

			template <class T>
			/// @brief Добавить UI элемент
			/// @param element
			/// @return std::pair<номер элемента в списке, указатель на элемент>
			T* AddElement(const T &element);

			template <class T>
			bool DeleteElement(T* element);

			/// @brief Снять фокус с этого окна
			void Unfocus() const;

			/// @brief Поставить фокус на это окно
			void Focus() const;

			/// @brief Отрисовать все элементы
			void RenderAllElements() const;

		private:
			/// @brief Заголовок окна
			std::string _title;


			/// @brief Список всех кнопок этого окна
			std::vector<UIElement*> _Elements;

			/// @brief Цвета окна
			Colors::ColorsTable _colors;

			/// @brief отступы от края окна
			uint8_t _MARGIN;

			/// @brief Стиль окна
			uint8_t _style;

			/// @brief Прозрачность окна
			uint8_t _Transparency;

			/// @brief Активная форма
			mutable int activeForm = -1;

			/// @brief Окно перерисовывается сейчас (да/нет)
			mutable bool _Redraw = false;

			/// @brief Окно пересовывается при перетаскивании
			bool _RealtimeRedraw;
		};

		//=============================================================================================================================================================

		template <class T>
		T* KolibriLib::window::Window::AddElement(const T &element)
		{
			#ifdef DEBUG
			_ksys_debug_puts("Add element:");
			#endif

			T *p = new T(element);
			if (p->GetParent())
			{
				p->SetParent(this);	// сдес ашибка, при вызове Render вызывается Parent.get()->GetAbsoluteCoord() и на нём падает приложение
			}


			_Elements.push_back((UIElement*)p);

			#ifdef DEBUG
			_ksys_debug_puts("done\n");
			#endif

			return p;
		}

		template<class T>
		bool Window::DeleteElement(T * element)
		{
			#ifdef DEBUG
			_ksys_debug_puts("delete element:");
			#endif

			auto a = std::find(_Elements.begin(), _Elements.end(), element);

			if(a == _Elements.end())
			{
				return false;
			}
			else
			{
				delete _Elements[_Elements.begin() - a];
				return true;
			}

			#ifdef DEBUG
			_ksys_debug_puts("done\n");
			#endif
		}

		KolibriLib::window::Window::Window(const std::string &Title, const KolibriLib::Size &size, const KolibriLib::Colors::ColorsTable &colors, bool Resize, bool RealtimeRedraw, bool Gradient, unsigned Transparency, const unsigned &Margin)
			:	_title	(Title), 
				_colors	(colors),
				_MARGIN	(Margin),
				_Transparency	(Transparency),
				_RealtimeRedraw	(RealtimeRedraw)
		{
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

			window::CreateWindow(
				DefaultWindowCoord, 
				size, 
				_title, 
				_colors.win_body, 
				_colors.win_title, 
				_style
			);
		}

		KolibriLib::window::Window::~Window()
		{
			for(auto n : _Elements)
			{
				if(!(n == nullptr))
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

		UI::UDim KolibriLib::window::Window::GetCoord() const
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

			StartRedraw();
			window::CreateWindow(GetAbsoluteCoord(), {0,0}, _title, _colors.win_body, _colors.win_title, _style);

			if(_style & window::WindowStyle::CanResize)
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
				RenderAllElements();
			}

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
		}

		void Window::Render(const Coord &coord)
		{
			#ifdef DEBUG
			_ksys_debug_puts("Render window:");
			#endif
			
			StartRedraw();
			window::CreateWindow({0,0}, {0, 0}, _title, _colors.win_body, _colors.win_title, _style);

			KolibriLib::graphic::DrawRectangleFill({0, (int)window::GetSkinHeight()}, GetWindowSize(), _colors.win_body);

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

		unsigned Window::GetMargin() const
		{
			return _MARGIN;
		}

		inline UI::UDim Window::GetSize() const
		{
			Size p = GetAbsoluteSize();
			return UI::UDim(0, p.x, 0, p.y);
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

				if(mouse::MouseButtons::RightButton && mouse::MouseButtons())	// Если нажата правая кнопка
				{
					Coord m = mouse::GetMousePositionInWindow();

					if(m.x < GetSize().GetAbsolute().x && m.y < window::GetSkinHeight())
					{
						
					}
				}

				break;
			}
			if (_RealtimeRedraw)
			{
				Coord Mouse = mouse::GetMousePositionInWindow();
				if (((Mouse.x > 0 && Mouse.y > 0) && Mouse.x < GetWindowSize().x && Mouse.y < GetSkinHeight()) && mouse::GetMouseButtons() == mouse::LeftButton)
				{
					while (mouse::GetMouseButtons() == mouse::LeftButton)
					{
						Render(mouse::GetMousePositionOnSreen() - Mouse);
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
		}

		void KolibriLib::window::Window::Unfocus() const
		{
			_ksys_unfocus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
		}

		void KolibriLib::window::Window::Focus() const
		{
			_ksys_focus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
		}
	} // namespace window

}

#endif
