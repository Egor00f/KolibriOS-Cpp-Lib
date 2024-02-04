#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>


#include <sys/ksys.h>


#include "input.hpp"
#include "os.hpp"
#include "windowBase.hpp"
#include "button.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "form.hpp"
#include "frame.hpp"

namespace KolibriLib
{ //=============================================================================================================================================================

	

	/// \brief Работа с окном
	namespace window
	{
		

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
				Frame
			};

			
			UI::buttons::Button btn;
			UI::text::TextLabel txt;
			UI::Form frm;
			UI::CheckBox ChckBx;
			UI::Images::image img;
			UI::Frame frame;
			

			unsigned _type;
			unsigned DrawPrioritet;
			bool use;
			
		};

		/// @brief Класс для работы с окном
		class Window
		{
		private:
			/// @brief Заголовок окна
			std::string _title;

			/// @brief Размеры окна
			UI::Size _size;

			/// @brief Цвета окна
			Color::ColorsTable _colors;

			/// @brief отступы от края окна
			unsigned _MARGIN;

			/// @brief Стиль окна
			int _style;

			/// @brief Активная фарма
			unsigned int activeForm;

			/// @brief Окно перерисовывается сейчас (да/нет)
			bool _Redraw = false;


			/// @brief Список всех кнопок этого окна
			std::vector<Element> _Elements;

			/// @brief Добавить в список новую кнопку
			/// @param btn кнопка
			/// @return номер в списке @link _Buttons
			unsigned AddNewButton(UI::buttons::Button btn);

			/// @brief Добавить в список новую текствую метку
			/// @param text текстовая метка
			/// @return номер в списке @link _Texts
			unsigned AddNewTextLabel(UI::text::TextLabel text);

			/// @brief Добавить форму
			/// @param form Форма
			/// @return номер в списке @link _Forms
			unsigned AddNewForm(UI::Form form);

		public:
			/// @brief Конструктор
			/// @param Title Заголовок окна
			/// @param size Размер окна
			/// @param style стиль окна
			/// @param colors Цвет окна
			/// @param Margin Отступы
			Window(std::string Title = "Window", UI::Size size = DefaultWindowSize, int style = 0x14, Color::ColorsTable colors = Color::DefaultColorTable, unsigned Margin = 0);
			~Window();

			/// @brief Отрисовать окно
			void Render();

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin();

			/// @brief Получить размер окна
			/// @return @link _size
			UI::Size GetSize();

			/// @brief Задать стандартные цвета окна
			/// @param colorTable таблица цветов
			void SetWindowColors(const Color::ColorsTable& colorTable);

			/// @brief Начать перересовку окна
			/// @paragraph Стирает всё что было нарисованно в окне
			/// @paragraph Обязательно после должна быть вызвана функция #EndRedraw()
			void StartRedraw();

			/// @brief Закончить перересовку окна
			/// @paragraph Обязательно после должна быть вызвана функция #StartRedraw()
			void EndRedraw();

			/// @brief Отрисовать окно
			/// @param coord позиция окна
			/// @param size размер окна
			/// @param title титул(текст в заголовке)
			/// @param color цвет рабочей области
			/// @param style стиль
			void DrawWindow(UI::Coord coord = mouse::GetMousePositionOnSreen());

			/// @brief Изменить окно
			/// @param coord позиция
			/// @param size размер
			void ChangeWindow(UI::Coord coord, UI::Size size);

			/// @brief Изменить заголовок окна
			/// @param newTitle новый заголовок
			void ChangeTilte(std::string newTitle);

			/// @brief Получить размер окна
			/// @return point.x - ширина окна,
			/// @return point.y - высота окна
			UI::Size GetWindowSize();

			/// @brief Создать кнопку
			/// @param coord координата кнопки
			/// @param size размеры кнопки
			/// @param Text текст кнопки
			/// @param margin Отступы границ кноки от текста
			/// @param UseWindowColors Использовать ли цвет окна(да/нет)
			/// @param color Цвет кнопки
			/// @param TextColor Цвет текста кнопки
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(UI::Coord coord = {0, 0}, UI::Size size = {16, 16}, std::string Text = " ", unsigned margin = UI::DefaultMargin, bool UseWindowColors = true, Color::Color color = OS::sys_color_table.work_button, Color::Color TextColor = OS::sys_color_table.work_button_text);

			/// @brief Создать кнопку
			/// @param btn кнопка
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(const UI::buttons::Button& btn);

			/// @brief Получить кнопку
			/// @param id Номер кнопки в списке
			/// @return Кнопка
			UI::buttons::Button GetButton(unsigned id);

			/// @brief Создать текст в окне
			/// @param coord координата текста
			/// @param size рамер рамок текста
			/// @param text Сам текст
			/// @param FontSize Рамер текста
			/// @param UseWindowColors Использовать цвета окна(да/нет)
			/// @param color Цвет текста
			/// @return Номер текста в списке @link _Texts
			unsigned CreateText(UI::Coord coord = {0, 0}, UI::Size size = {16, 16}, std::string text = "Text", unsigned FontSize = 9, bool UseWindowColors = true, Color::Color color = OS::sys_color_table.work_text);

			/// @brief Создать текст в окне
			/// @param text текст
			/// @returnНомер текста в списке @link _Texts
			unsigned CreateText(const UI::text::TextLabel& text);

			/// @brief Изменить текст
			/// @param N Номер элемента в списке
			/// @param text Новая текстовая метка
			void SetTextLabel(unsigned N, const UI::text::TextLabel &text);

			/// @brief Создать форму
			/// @param form форма
			/// @return номер в списке @link _Forms
			unsigned CreateForm(UI::Form form);

			/// @brief Удалить элемент
			/// @param id idшник того элемента, которой нужно удалить
			void DeleteElement(unsigned id);

			/// @brief Обработчик окна
			/// @return Ивент
			OS::Event Handler();

			/// @brief Проверить какая нажата
			UI::buttons::ButtonID GetPressedButton();

			/// @brief Получить текст введённый в форму
			/// @param form номер формы в списке
			/// @return Функция возвращает текст введённый в формы
			std::string GetInputFromFrom(unsigned form);

			/// @brief Обработчик окна в отдельном потоке
			void HandlerThread();

			/// @brief Добавить UI элемент
			/// @param element 
			void AddElement(const UI::UIElement& element);
		};

		unsigned Window::AddNewButton(UI::buttons::Button btn)
		{
            for(unsigned i = 0; i < _Elements.size(); i++)
			{
				if (!_Elements[i].use)
				{
					switch (btn.GetType())
					{
					case UI::buttons::Button::Type::Image:
						_Elements[i].btn = btn;
						break;
					case UI::buttons::Button::Type::Text:
						_Elements[i].btn.init(btn.GetCoord(), btn.GetSize(), btn.GetTextLabel(), btn.GetMargin(), btn.GetColor());
						break;
					default:
						break;
					}
					_Elements[i]._type = Element::Type::Button;
					_Elements[i].use = true;
					return i;
				}
			}
			Element a;
			switch (btn.GetType())
			{
			case UI::buttons::Button::Type::Image:
				a.btn.init(btn.GetCoord(), btn.GetSize(), btn.GetImage(), btn.GetMargin(), btn.GetColor());
				break;
			case UI::buttons::Button::Type::Text:
				a.btn.init(btn.GetCoord(), btn.GetSize(), btn.GetTextLabel(), btn.GetMargin(), btn.GetColor());
			default:
				break;
			}
			a.use = true;
			_Elements.push_back(a);
			return _Elements.size();
		}

        unsigned Window::AddNewTextLabel(UI::text::TextLabel text)
        {
			_ksys_debug_puts("AddNewText:");
			for (unsigned i = 0; i < _Elements.size(); i++)
			{
				char *a = "find, try №";
				char *b = (char*)('0' + (char)i);
				strcat(b, ".\n");
				strcat(a, b);
				_ksys_debug_puts(a);
				if (!_Elements[i].use)
				{
					_Elements[i].txt = text;
					_Elements[i]._type = Element::Type::TextLabel;
					_Elements[i].use = true;
					_ksys_debug_puts("done\n");
					return i;
				}
			}
			_ksys_debug_puts("\n\n==>Element:");
			Element a;
			_ksys_debug_puts("\na.use = true");
			a.use = true;
			_ksys_debug_puts("\ntxt.init()");
			a.txt.init(text.GetCoord(), text.GetSize(), text.GetText(), text.GetFontSize(), text.GetColor());
			_ksys_debug_puts("\n\nDONE!!!\n\n");
			_Elements.push_back(a);
		}

        unsigned Window::AddNewForm(UI::Form form)
        {
			for (unsigned i = 0; i < _Elements.size(); i++)
			{
				if (!_Elements[i].use)
				{
					_Elements[i].frm.init(form.GetCoord(), form.GetSize(), NULL, form.GetColor(), form.GetBackgroundColor(), form.GetMargin());
					_Elements[i]._type = Element::Type::Form;
					_Elements[i].use = true;
					return i;
				}
			}
			Element a;
			a.frm.init(form.GetCoord(), form.GetSize(), NULL, form.GetColor(), form.GetBackgroundColor(), form.GetMargin());
			a.use = true;
			a._type = Element::Type::Form;
			_Elements.push_back(a);
			return _Elements.size();
		}

        Window::Window(std::string Title, UI::Size size, int style, Color::ColorsTable colors, unsigned Margin)
        {
			_ksys_debug_puts("window:");
			_title = Title;
			_size = size;
			_style = style;
			_MARGIN = Margin;

			if (Color::ComparisonColorsTables(colors, Color::DefaultColorTable))	//Если небыла в аргументах таблица цветов
			{																		//Используется системная
				_colors = OS::GetSystemColors();
			}
			else
			{
				_colors = colors;
			}
			
			DrawWindow(DefaultWindowCoord);											//Отрисовать окно
		}

		Window::~Window()
		{
			
		}

		void Window::SetWindowColors(const Color::ColorsTable& colorTable)
		{
			_colors = colorTable;
		}

		void Window::StartRedraw()
		{
			_ksys_start_draw();
			_Redraw = true;
		}

		void Window::EndRedraw()
		{
			if (_Redraw)
			{
				_ksys_end_draw();
				_Redraw = false;
			}
		}

		void Window::DrawWindow(UI::Coord coord)
		{
			_ksys_create_window(coord.x, coord.y, _size.x, _size.y, _title.c_str(), _colors.work_area, _style);
		}

		void Window::ChangeWindow(UI::Coord coord, UI::Size size)
		{
			_size = size;
			_ksys_change_window(coord.x, coord.y, size.x, size.y);
		}

		void Window::ChangeTilte(std::string newTitle)
		{
			_ksys_set_window_title(newTitle.c_str());
		}

		UI::Size Window::GetWindowSize()
		{
			return _size;
		}
		void Window::Render()
		{
			StartRedraw();
			DrawWindow();

			for (unsigned i = 0; i < _Elements.size(); i++)
			{
				if (_Elements[i].use)
				{
					switch (_Elements[i]._type)
					{
					case Element::Type::Button:
						_Elements[i].btn.Render();
						break;
					case Element::Type::TextLabel:
						_Elements[i].txt.Render();
						break;
					case Element::Type::CheckBox:
						_Elements[i].ChckBx.Render();
						break;
					case Element::Type::Image:
						_Elements[i].img.Render();
						break;
					case Element::Type::Form:
						_Elements[i].frm.Render();
						break;
					default:
						_ksys_debug_puts("Error in KolibriLib::window::Window::Render(): unklown type\n");
						break;
					}
				}
			}

			EndRedraw();
		}

        unsigned Window::GetMargin()
        {
            return _MARGIN;
        }

        UI::Size Window::GetSize()
        {
            return _size;
        }

        unsigned KolibriLib::window::Window::CreateButton(UI::Coord coord, UI::Size size, std::string Text, unsigned margin, bool UseWindowColors, Color::Color color, Color::Color TextColor)
		{
			if(UseWindowColors)
			{
				color		= _colors.work_button;
				TextColor	= _colors.work_button_text;
			}
			return AddNewButton(UI::buttons::Button(coord, size, margin, color));
		}


        
        unsigned Window::CreateText(UI::Coord coord, UI::Size size, std::string text, unsigned FontSize, bool UseWindowColors, Color::Color color)
        {
			_ksys_debug_puts("CreateText:");
			if(UseWindowColors)
			{
				color = _colors.work_text;
			}

			return AddNewTextLabel(UI::text::TextLabel(coord, size, text, FontSize, true, color, _MARGIN));
		}

        unsigned Window::CreateText(const UI::text::TextLabel& text)
        {
            return AddNewTextLabel(UI::text::TextLabel(text));
        }

      
		
        void Window::DeleteElement(unsigned id)
		{
			_Elements[id].use = false;
		}


		OS::Event Window::Handler()
		{
			OS::Event event = OS::WaitEvent(10);

			switch (event)
			{
			case OS::Events::Redraw:

				Render();

				break;
			case OS::Events::Button:

				if(UI::buttons::GetPressedButton() == 1)	//Если нажата кнопка X
				{
					return OS::Events::Exit;
				}

				for (unsigned i = 0; i < _Elements.size(); i++)	//Запуск обработчиков всех используемых элементов
				{
					if (_Elements[i].use)
					{
						switch(_Elements[i]._type)
						{
						case Element::Type::Form:
						
							_Elements[i].frm.ButtonHandler();
						case Element::CheckBox:
							_Elements[i].ChckBx.Handler();
						case Element::Button:
							_Elements[i].btn.Handler();
						}
					}
				}

				break;
			case OS::Events::Key:
				
				_Elements[activeForm].frm.Handler();	//Обработчик активной на текущий момент формы
						
				break;
			}
			return event;
		}

		UI::buttons::ButtonID Window::GetPressedButton()
		{
			for(unsigned i = 0; i < _Elements.size(); i++)
			{
				if(_Elements[i]._type == Element::Type::Button)
				{
					if(_Elements[i].btn.GetStatus())
					{
						return _Elements[i].btn.GetId();
					}
				}
			}
		}
		std::string Window::GetInputFromFrom(unsigned form)
		{
			if(_Elements[form]._type == Element::Type::Form)
			{
				return _Elements[form].frm.GetInput();
			}
		}

		UI::buttons::Button Window::GetButton(unsigned id)
		{
			return _Elements[id].btn;
		}

		void Window::HandlerThread()
		{
			while(true)
			{
				if(Handler() == OS::Events::Exit)
				{
					break;
				}
			}
		}

		void Window::AddElement(const UI::UIElement& element)
		{

		}
	}

    //=============================================================================================================================================================

	

}




//=============================================================================================================================================================


#endif