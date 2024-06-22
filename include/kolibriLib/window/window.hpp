#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include <sys/ksys.h>

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
			
			/// @brief Номер элемента в Window::_Elements
			typedef int ElementNumber;

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
			UI::UDim GetSize() const;

			/// @brief Получить координаты окна
			/// @return
			UI::UDim GetCoord() const;


			/// @brief 
			/// @return 
			Coord GetAbsoluteCoord() const;

			/// @brief 
			/// @return 
			Size GetAbsoluteSize() const;

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

			/// @brief Удалить элемент
			/// @param id idшник того элемента, которой нужно удалить
			void DeleteElement(const Window::ElementNumber &id);

			/// @brief Обработчик окна
			/// @return Ивент
			OS::Event Handler();

			/// @brief Проверить какая нажата
			UI::buttons::ButtonID GetPressedButton();

			/// @brief Получить текст введённый в форму
			/// @param form номер формы в списке
			/// @return Функция возвращает текст введённый в формы
			std::string GetInputFromFrom(int form) const;

			template <class T>
			/// @brief Добавить UI элемент
			/// @param element
			/// @return std::pair<номер элемента в списке, указатель на элемент>
			ElementNumber AddElement(const T &element);

			template <class T>
			/// @brief Изменить элемент
			/// @param i
			/// @param element
			void SetElement(const Window::ElementNumber &i, const T &element);

			/// @brief Получить Window::Element
			/// @param i ключ
			/// @return
			UIElement* GetElement(int i);

			/// @brief Снять фокус с этого окна
			void Unfocus() const;
			/// @brief Поставить фокус на это окно
			void Focus() const;

			void RenderAllElements() const;

		private:
			/// @brief Заголовок окна
			std::string _title;

			/// @brief Список всех кнопок этого окна
			std::unordered_map<Window::ElementNumber, UIElement*> _Elements;

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
		Window::ElementNumber KolibriLib::window::Window::AddElement(const T &element)
		{
			#ifdef DEBUG
			_ksys_debug_puts("Add element-\n");
			#endif


			for (int i = 0; i < _Elements.max_size(); i++)
			{
				if (_Elements.count(i) == 0)
				{
					auto a = new T(element);
					a->SetParent(this);
					_Elements.emplace(i, a);

					return i;
				}
			}
			return -1;
		}

		template <class T>
		void KolibriLib::window::Window::SetElement(const ElementNumber &i, const T &element)
		{
			if (_Elements.count(i))
			{
				_Elements[i] = new T(element);
				return;
			}
			_ksys_debug_puts("KolibriLib::window::Window::SetElement: not found element\n");
			return;
		}

		KolibriLib::window::Window::Window(const std::string &Title, const KolibriLib::Size &size, const KolibriLib::Colors::ColorsTable &colors, bool Resize, bool RealtimeRedraw, bool Gradient, unsigned Transparency, const unsigned &Margin)
			: _title(Title), _colors(colors), _MARGIN(Margin), _Transparency(Transparency), _RealtimeRedraw(RealtimeRedraw)
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

			window::CreateWindow(DefaultWindowCoord, size, _title, _colors.win_body, _colors.win_title, _style);
		}

		KolibriLib::window::Window::~Window()
		{
			for(auto n : _Elements)
			{
				delete n.second;
			}
		}

		void Window::RenderAllElements() const
		{
			for (auto &it : _Elements)
			{
				it.second->Render();
			}
		}

		UIElement *KolibriLib::window::Window::GetElement(int i)
		{
			return _Elements.at(i);
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

			static Size LastWindowSize;

			if(window::GetWindowSize()  == LastWindowSize)
			{
				LastWindowSize = window::GetWindowSize();

				for (const auto n : _Elements)
				{
					if (n.second->RenderOnEverythingRedraw)
					{
						n.second->Render();
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

			StartRedraw();
			window::CreateWindow(GetCoord().GetAbsolute(), {0, 0}, _title, _colors.win_body, _colors.win_title, _style);

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
		}

		unsigned Window::GetMargin() const
		{
			return _MARGIN;
		}


		void Window::DeleteElement(const ElementNumber &id)
		{
			if (_Elements.count(id))
			{
				if (activeForm == id)
				{
					activeForm = -1;
				}
				delete _Elements[id];
				_Elements.erase(_Elements.find(id));
				return;
			}
			_ksys_debug_puts("element with this id not found\n");
		}

		OS::Event Window::Handler()
		{
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

				for (const auto &it : _Elements) // Запуск обработчиков всех используемых элементов
				{
					const char *a = it.second->ClassName.c_str();
					if (a == "Form")
						((UI::Form *)it.second)->ButtonHandler();
					else if (a == "CheckBox")
						((UI::CheckBox *)it.second)->Handler();
					else if (a == "Button")
						((UI::buttons::Button *)it.second)->Handler();
				}

				break;
			case OS::Events::Key:

				if (activeForm != -1 && _Elements[activeForm]->ClassName == "Form")
				{
					((UI::Form *)_Elements[activeForm])->Handler(); // Обработчик активной на текущий момент формы
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

				for(const auto n : _Elements)
				{
					if(n.second->ClassName == "Frame")
					{
						((UI::Frame*)n.second)->Handler();
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
			for (const auto &n : _Elements)
			{
				if (n.second->ClassName == "Button")
				{
					if (((UI::buttons::Button *)n.second)->GetStatus())
					{
						return ((UI::buttons::Button *)n.second)->GetId();
					}
				}
			}
		}
		std::string Window::GetInputFromFrom(int form) const
		{
			auto it = _Elements.find(form);
			if (it->second->ClassName == "Form")
			{
				return ((UI::Form *)it->second)->GetInput();
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