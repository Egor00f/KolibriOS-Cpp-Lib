#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>
#include <map>
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
		class Window
		{
		private:
			/// @brief Структура содержащая элемент
			struct Element
			{
				enum Type
				{
					None = 0,
					Button,
					Image,
					CheckBox,
					Form,
					TextLabel,
					Frame,
					Menu
				};

				UI::buttons::Button * btn;
				UI::Images::Image   * img;
				UI::CheckBox        * checkbox;
				UI::Form            * form;
				UI::text::TextLabel * txt;
				UI::Menu            * menu;
				UI::Frame           * frame;

				unsigned _type;

				Element();
				~Element();

				template <class T>
				void SetElement(const T& elem);

				void free();
			};

			/// @brief Заголовок окна
			std::string _title;

			/// @brief Список всех кнопок этого окна
			std::map<int, Element> _Elements;

			/// @brief Размеры окна
			Size _size;

			/// @brief Цвета окна
			Colors::ColorsTable _colors;

			Colors::Color _TitleColor;

			/// @brief отступы от края окна
			unsigned _MARGIN;

			/// @brief Стиль окна
			unsigned _style;

			/// @brief Прозрачность окна
			unsigned _Transparency;

			/// @brief Активная фарма
			mutable int activeForm = -1;

			/// @brief Окно перерисовывается сейчас (да/нет)
			mutable bool _Redraw = false;

			/// @brief Окно пересовывается при перетаскивании
			bool _RealtimeRedraw;

		public:
			/// @brief Конструктор
			/// @param Title Заголовок окна
			/// @param size Размер окна
			/// @param style стиль окна
			/// @param colors Цвет окна
			/// @param Margin Отступы
			Window(const std::string &Title = "Window", const Size &size = DefaultWindowSize, const Colors::ColorsTable &colors = Colors::DefaultColorTable, const Colors::Color &TitleColor = OS::GetSystemColors().work_graph, bool Resize = false, bool RealtimeReadraw = false, bool Gradient = false, unsigned Transparency = 0, const unsigned &Margin = 0);
			~Window();

			/// @brief Полная перересовка окна
			void Redraw();

			/// @brief Отрисовать окно
			void Render(const Coord& coord = DefaultWindowCoord);

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin() const;

			/// @brief Получить размер окна
			/// @return @link _size
			const Size& GetSize() const;

			/// @brief Задать стандартные цвета окна
			/// @param colorTable таблица цветов
			void SetWindowColors(const Colors::ColorsTable& colorTable);

			/// @brief Начать перересовку окна
			/// @paragraph Стирает всё что было нарисованно в окне
			/// @paragraph Обязательно после должна быть вызвана функция #EndRedraw()
			void StartRedraw() const;

			/// @brief Закончить перересовку окна
			/// @paragraph Обязательно после должна быть вызвана функция #StartRedraw()
			void EndRedraw() const;

			/// @brief Получить координаты окна
			/// @return 
			Coord GetCoord() const;

			/// @brief Изменить окно
			/// @param coord позиция
			/// @param size размер
			void ChangeWindow(const Coord& coord, const Size& size);

			/// @brief Изменить заголовок окна
			/// @param newTitle новый заголовок
			void ChangeTilte(const std::string& newTitle);

			/// @brief Получить размер окна
			/// @return point.x - ширина окна,
			/// @return point.y - высота окна
			Size GetWindowSize() const;

			/// @brief Удалить элемент
			/// @param id idшник того элемента, которой нужно удалить
			void DeleteElement(int id);

			/// @brief Обработчик окна
			/// @return Ивент
			OS::Event Handler();

			/// @brief Проверить какая нажата
			UI::buttons::ButtonID GetPressedButton();

			/// @brief Получить текст введённый в форму
			/// @param form номер формы в списке
			/// @return Функция возвращает текст введённый в формы
			const std::string& GetInputFromFrom(int form) const;

			template <class T>
			/// @brief Добавить UI элемент
			/// @param element
			int AddElement(const T &element);

			template <class T>
			/// @brief Изменить элемент
			/// @tparam T
			/// @param i
			/// @param element
			void SetElement(int i, const T& element);

			/// @brief
			/// @tparam T
			/// @param i
			/// @return
			template <class T>
			const T& GetElement(int i) const;

			/// @brief Снять фокус с этого окна
			void Unfocus() const;
			/// @brief Поставить фокус на это окно
			void Focus() const;
		};

		//=============================================================================================================================================================

		template <class T>
		void KolibriLib::window::Window::Element::SetElement(const T &elem)
		{
			_ksys_debug_puts("Error in KolibriLib::window::Window::Element::SetElement: unklown type");
		}

		//-------------------------------------------------------------------------------------------------------------------------------------------------------------
		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::buttons::Button>(const KolibriLib::UI::buttons::Button &elem)
		{
			free();
			btn = new UI::buttons::Button(elem);
			_type = Type::Button;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::Images::Image>(const KolibriLib::UI::Images::Image &elem)
		{
			free();
			img = new UI::Images::Image(elem);
			_type = Type::Image;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::CheckBox>(const KolibriLib::UI::CheckBox &elem)
		{
			free();
			checkbox = new UI::CheckBox(elem);
			_type = Type::CheckBox;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::Form>(const KolibriLib::UI::Form &elem)
		{
			free();
			form = new UI::Form(elem);
			_type = Type::Form;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::text::TextLabel>(const KolibriLib::UI::text::TextLabel &elem)
		{
			free();
			txt = new UI::text::TextLabel(elem);
			_type = Type::TextLabel;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::Menu>(const KolibriLib::UI::Menu &elem)
		{
			free();
			menu = new UI::Menu(elem);
			_type = Type::Menu;
		}

		template <>
		void KolibriLib::window::Window::Element::SetElement<KolibriLib::UI::Frame>(const KolibriLib::UI::Frame &elem)
		{
			free();
			frame = new UI::Frame(elem);
			_type = Type::Frame;
		}

		template <class T>
		int KolibriLib::window::Window::AddElement(const T &element)
		{
			_ksys_debug_puts("Add element\n");
			Element a;

			a.SetElement(element);

			for (int i = 0; i < _Elements.size(); i++)
			{
				if (_Elements.count(i) == 0)
				{
					_Elements[i] = a;
					return i;
				}
			}
		}

		template <class T>
		void KolibriLib::window::Window::SetElement(int i, const T &element)
		{
			if (_Elements.count(i))
			{
				_Elements[i].SetElement(element);
				return;
			}
			_ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");
		}

		template <class T>
		const T &KolibriLib::window::Window::GetElement(int i) const
		{
			auto it = _Elements.find(i);
			if (it != _Elements.end())
			{
				switch (it->second._type)
				{
				case Element::Type::TextLabel:
					return it->second.txt;
				case Element::Type::Button:
					return it->second.btn;
				case Element::Type::Image:
					return it->second.img;
				case Element::Type::Form:
					return it->second.form;
				case Element::Type::CheckBox:
					return it->second.checkbox;
				case Element::Type::Frame:
					return it->second.frame;
				case Element::Type::Menu:
					return it->second.menu;
				default:
					_ksys_debug_puts("KolibriLib::window::Window::GetElement: unknown type, break\n");
					break;
				}
			}
			_ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");

			return 0;
		}

		KolibriLib::window::Window::Element::Element()
		{
			#if DEBUG == true
			_ksys_debug_puts("KolibriLib::window::Window::Element constructor\n");
			#endif
			_type = KolibriLib::window::Window::Element::Type::None;
		}

		KolibriLib::window::Window::Element::~Element()
		{
			free();
		}

		void KolibriLib::window::Window::Element::free()
		{
			switch (_type)
			{
			case Type::Button:
				delete btn;
				break;
			case Type::Image:
				delete img;
				break;
			case Type::CheckBox:
				delete checkbox;
				break;
			case Type::Form:
				delete form;
				break;
			case Type::TextLabel:
				delete txt;
				break;
			case Type::Menu:
				delete menu;
				break;
			case Type::Frame:
				delete frame;
				break;
			default:
				break;
			}
		}

		//=============================================================================================================================================================

		KolibriLib::window::Window::Window(const std::string &Title, const KolibriLib::Size &size, const KolibriLib::Colors::ColorsTable &colors, const KolibriLib::Colors::Color &TitleColor, bool Resize, bool RealtimeRedraw, bool Gradient, unsigned Transparency, const unsigned &Margin)
		{
			#if DEBUG == true
			_ksys_debug_puts("KolibriLib::window:::Window constructor\n");
			#endif

			_title = Title;
			_size = size;
			_MARGIN = Margin;
			_TitleColor = TitleColor;
			_Transparency = Transparency;
			_RealtimeRedraw = RealtimeRedraw;

			/*DCBAYYYY*/
			_style = 0b00100000;
			if (Resize)
			{
				_style += WindowStyle::CanResize;
			}
			else
			{
				_style += WindowStyle::FixSize;
			}

			if (Gradient)
			{
				_style += WindowStyle::GradientDraw;
			}

			if (colors == Colors::DefaultColorTable) // Если небыла в аргументах таблица цветов
			{										 // Используется системная
				_colors = OS::GetSystemColors();
			}
			else
			{
				_colors = colors;
			}

			if (_Transparency > 0)
			{
				_style += WindowStyle::NoDrawWorkspace;
			}

			window::CreateWindow(DefaultWindowCoord, _size, _title, _colors.work_area, _TitleColor, _style); // Отрисовать окно
		}

		KolibriLib::window::Window::~Window()
		{
		}

		void KolibriLib::window::Window::Redraw()
		{
			StartRedraw();
			ChangeWindow(GetCoord(), _size);

			if (_Transparency > 0 && false)
			{
				/*UI::Images::img buff;
				for (unsigned i = 0; i < GetWindowSize().y; i++)
				{
					for (unsigned j = 0; j < GetWindowSize().x; j++)
					{
						buff.SetPixel(Colors::BlendColors(Background::ReadPoint(Coord(j, i)), , _Transparency / 100))

					}
				}*/
			}
			else
			{
				KolibriLib::graphic::DrawRectangleFill({0, (int)window::GetSkinHeight()}, GetWindowSize(), _colors.frame_area);
			}

			for (const std::pair<int, Window::Element> &n : Window::_Elements)
			{
				switch (n.second._type)
				{
				case KolibriLib::window::Window::Element::Type::TextLabel:
					n.second.txt->Render();
					break;
				case KolibriLib::window::Window::Element::Type::Button:
					n.second.btn->Render();
					break;
				case KolibriLib::window::Window::Element::Type::Image:
					n.second.img->Render();
					break;
				case KolibriLib::window::Window::Element::Type::Form:
					n.second.form->Render();
					break;
				case KolibriLib::window::Window::Element::Type::CheckBox:
					n.second.checkbox->Render();
					break;
				case KolibriLib::window::Window::Element::Type::Frame:
					n.second.frame->Render();
					break;
				case KolibriLib::window::Window::Element::Type::Menu:
					n.second.menu->Render();
					break;
				default:
					_ksys_debug_puts("KolibriLib::window::Window::Render unknown type, break\n");
					break;
				}
			}

			if (_Transparency != 0) // Прозрачность окна
			{
				for (int i = 0; i < _size.y; i++)
				{
					for (int j = 0; j < _size.x; j++)
					{
						graphic::DrawPixel({j, i}, Colors::BlendColors(graphic::ReadPoint({j, i}), Background::ReadPoint({j, i}), 100 / _Transparency)); // Пока так, потом может быть станет лучше
					}
				}
			}

			EndRedraw();
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

		Coord KolibriLib::window::Window::GetCoord() const
		{
			window::GetWindowCoord();
		}

		void Window::ChangeWindow(const Coord &coord, const Size &size)
		{
			_size = size;
			_ksys_change_window(coord.x, coord.y, size.x, size.y);
		}

		void Window::ChangeTilte(const std::string &newTitle)
		{
			_ksys_set_window_title(newTitle.c_str());
		}

		Size Window::GetWindowSize() const
		{
			return _size;
		}

		void Window::Render(const Coord &coord)
		{
			StartRedraw();
			window::CreateWindow(coord, _size, _title, _colors.work_area, _TitleColor, _style);

			for (const std::pair<int, Element> &n : _Elements)
			{
				switch (n.second._type)
				{
				case Element::Type::TextLabel:
					n.second.txt->Render();
					break;
				case Element::Type::Button:
					n.second.btn->Render();
					break;
				case Element::Type::Image:
					n.second.img->Render();
					break;
				case Element::Type::Form:
					n.second.form->Render();
					break;
				case Element::Type::CheckBox:
					n.second.checkbox->Render();
					break;
				case Element::Type::Menu:
					n.second.menu->Render();
					break;
				case Element::Type::Frame:
					n.second.frame->Render();
					break;
				default:
					break;
				}
			}

			if (_Transparency != 0) // Прозрачность окна
			{
				Size size = GetWindowSize();
				for (int i = 0; i < size.y; i++)
				{
					for (int j = 0; j < size.x; j++)
					{
						graphic::DrawPixel({j, i}, Colors::BlendColors(graphic::ReadPoint({j, i}), Background::ReadPoint({j, i}), 100 / _Transparency));
					}
				}
			}

			EndRedraw();
		}

		unsigned Window::GetMargin() const
		{
			return _MARGIN;
		}

		const Size &Window::GetSize() const
		{
			return _size;
		}

		void Window::DeleteElement(int id)
		{
			if (_Elements.count(id))
			{
				if (activeForm == id)
				{
					activeForm = -1;
				}
				_Elements.erase(id);
			}
		}

		OS::Event Window::Handler()
		{
			OS::Event event = OS::WaitEvent(8);

			switch (event)
			{
			case OS::Events::Redraw:

				Render();

				break;
			case OS::Events::Button:

				if (UI::buttons::GetPressedButton() == 1) // Если нажата кнопка X
				{
					return OS::Events::Exit;
				}

				for (const std::pair<int, Element> &n : _Elements) // Запуск обработчиков всех используемых элементов
				{
					switch (n.second._type)
					{
					case Element::Type::Form:
						n.second.form->ButtonHandler();
					case Element::CheckBox:
						n.second.checkbox->Handler();
					case Element::Button:
						n.second.btn->Handler();
					}
				}

				break;
			case OS::Events::Key:

				if (activeForm != -1)
				{
					_Elements[activeForm].form->Handler(); // Обработчик активной на текущий момент формы
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
			for (const std::pair<int, Element> &n : _Elements)
			{
				if (n.second._type == Element::Type::Button)
				{
					if (n.second.btn->GetStatus())
					{
						return n.second.btn->GetId();
					}
				}
			}
		}
		const std::string &Window::GetInputFromFrom(int form) const
		{
			auto it = _Elements.find(form);
			if (it->second._type == Window::Element::Type::Form)
			{
				return it->second.form->GetInput();
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