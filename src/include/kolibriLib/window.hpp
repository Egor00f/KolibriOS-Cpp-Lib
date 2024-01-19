#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>


#include <sys/ksys.h>

#include "base.hpp"
#include "mouse.hpp"
#include "os.hpp"
#include "windowBase.hpp"
#include "button.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "form.hpp"

namespace KolibriLib
{ //=============================================================================================================================================================

	

	/// \brief Работа с окном
	namespace window
	{
		

		struct Element
		{
			enum class Type
			{
				Button,
				Image,
				CheckBox,
				Form,
				TextLabel
			};

			union
			{
				UI::buttons::Button btn;
				UI::text::TextLabel txt;
				UI::Form frm;
				UI::CheckBox CheckBox;
				UI::Images::image img;
			};

			Type type;
			bool use;

			Element(Type t)
			{
				type = t;
				use = false;
			}
			~Element()
			{
				switch (type)
				{
				case Element::Type::Button:
					btn.~Button();
					break;
				case Element::Type::CheckBox:
					CheckBox.~CheckBox();
				case Element::Type::TextLabel:
					txt.~TextLabel();
				case Element::Type::Form:
					frm.~Form();
				case Element::Type::Image:
					img.~image();
				default:
					break;
				}
			}
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
			Window(std::string Title = "Window", UI::Size size = DefaultWindowSize, int style = 0x14, ksys_colors_table_t colors = Color::DefaultColorTable, unsigned Margin = 0);
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
			void SetWindowColors(ksys_colors_table_t colorTable);

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
			unsigned CreateButton(UI::Coord coord = {0, 0}, UI::Size size = {16, 16}, std::string Text = " ", unsigned margin = UI::DefaultMargin, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_button_text);

			/// @brief Создать кнопку
			/// @param btn кнопка
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(const UI::buttons::Button& btn);

			

			/// @brief Создать текст в окне
			/// @param coord координата текста
			/// @param size рамер рамок текста
			/// @param text Сам текст
			/// @param FontSize Рамер текста
			/// @param UseWindowColors Использовать цвета окна(да/нет)
			/// @param color Цвет текста
			/// @return Номер текста в списке @link _Texts
			unsigned CreateText(UI::Coord coord = {0, 0}, UI::Size size = {16, 16}, std::string text = "Text", unsigned FontSize = 9, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_text);

			/// @brief Создать текст в окне
			/// @param text текст
			/// @returnНомер текста в списке @link _Texts
			unsigned CreateText(UI::text::TextLabel text);

			

			/// @brief Создать форму
			/// @param form форма
			/// @return номер в списке @link _Forms
			unsigned CreateForm(UI::Form form);

			/// @brief Удалить элемент
			/// @param id idшник того элемента, которой нужно удалить
			void DeleteElement(unsigned id);

			/// @brief Обработчик окна
			OS::Event Handler();
		};

		unsigned Window::AddNewButton(UI::buttons::Button btn)
		{
            for(unsigned i = 0; i < _Elements.size(); i++)
			{
				if (!_Elements[i].use)
				{
					switch (btn.GetType())
					{
					case UI::buttons::ContentType::Image:
						_Elements[i].btn.init(btn.GetCoord(), btn.GetSize(), btn.GetImage(), btn.GetMargin(), btn.GetColor());
						break;
					case UI::buttons::ContentType::Text:
						_Elements[i].btn.init(btn.GetCoord(), btn.GetSize(), btn.GetTextLabel(), btn.GetMargin(), btn.GetColor());
						break;
					default:
						break;
					}
					_Elements[i].type = Element::Type::Button;
					_Elements[i].use = true;
					return i;
				}
			}
			Element a(Element::Type::Button);
			switch (btn.GetType())
			{
			case UI::buttons::ContentType::Image:
				a.btn.init(btn.GetCoord(), btn.GetSize(), btn.GetImage(), btn.GetMargin(), btn.GetColor());
				break;
			case UI::buttons::ContentType::Text:
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
			for (unsigned i = 0; i < _Elements.size(); i++)
			{
				if (!_Elements[i].use)
				{
					_Elements[i].txt = text;
					_Elements[i].type = Element::Type::TextLabel;
					_Elements[i].use = true;
					return i;
				}
			}
			Element a(Element::Type::TextLabel);
			a.txt = text;
			a.use = true;
			_Elements.push_back(a);
		}

        inline unsigned Window::AddNewForm(UI::Form form)
        {
			for (unsigned i = 0; i < _Elements.size(); i++)
			{
				if (!_Elements[i].use)
				{
					_Elements[i].frm.init(form.GetCoord(), form.GetSize(), NULL, form.GetColor(), form.GetBackgroundColor(), form.GetMargin());
					_Elements[i].use = true;
					return i;
				}
			}
			Element a(Element::Type::Form);
			a.frm.init(form.GetCoord(), form.GetSize(), NULL, form.GetColor(), form.GetBackgroundColor(), form.GetMargin());
			a.use = true;
			_Elements.push_back(a);
			return _Elements.size();
		}

        Window::Window(std::string Title, UI::Size size, int style, ksys_colors_table_t colors, unsigned Margin)
        {
			_title = Title;
			_size = size;
			_style = style;
			if (Color::ComparisonColorsTables(colors, Color::DefaultColorTable))
			{
				_colors = OS::GetSystemColors();
			}
			else
			{
				_colors = colors;
			}
			_MARGIN = Margin;
			DrawWindow(DefaultWindowCoord);
		}

		Window::~Window()
		{
			for(unsigned i = 0; i < _Elements.size(); i++)
			{
				_Elements[i].use = false;
				switch (_Elements[i].type)
				{
				case Element::Type::Button:
					_Elements[i].btn.~Button();
					break;
				case Element::Type::CheckBox:
					_Elements[i].CheckBox.~CheckBox();
				case Element::Type::TextLabel:
					_Elements[i].txt.~TextLabel();
				case Element::Type::Form:
					_Elements[i].frm.~Form();
				case Element::Type::Image:
					_Elements[i].img.~image();
				default:
					break;
				}
			}
		}

		void Window::SetWindowColors(ksys_colors_table_t colorTable)
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
					switch (_Elements[i].type)
					{
					case Element::Type::Button:
						_Elements[i].btn.Render();
						break;
					case Element::Type::TextLabel:
						_Elements[i].txt.Render();
						break;
					case Element::Type::CheckBox:
						_Elements[i].CheckBox.Render();
						break;
					case Element::Type::Image:
						_Elements[i].img.Render();
						break;
					default:
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

        unsigned KolibriLib::window::Window::CreateButton(UI::Coord coord, UI::Size size, std::string Text, unsigned margin, bool UseWindowColors, ksys_color_t color, ksys_color_t TextColor)
		{
			if(UseWindowColors)
			{
				color		= _colors.work_button;
				TextColor	= _colors.work_button_text;
			}
			;
			return AddNewButton(UI::buttons::Button(coord, size, margin, color));
		}


        
        unsigned Window::CreateText(UI::Coord coord, UI::Size size, std::string text, unsigned FontSize, bool UseWindowColors, ksys_color_t color)
        {
            if(UseWindowColors)
			{
				color = _colors.work_text;
			}

			UI::text::TextLabel t(coord, size, text, FontSize);

			return AddNewTextLabel(t);
			
        }
        unsigned Window::CreateText(UI::text::TextLabel text)
        {
            return AddNewTextLabel(text);
        }

      
		
        void Window::DeleteElement(unsigned id)
		{
			_Elements[id].use = false;
			switch (_Elements[id].type)
			{
			case Element::Type::Button:
				_Elements[id].btn.~Button();
				break;
			case Element::Type::CheckBox:
				_Elements[id].CheckBox.~CheckBox();
			case Element::Type::TextLabel:
				_Elements[id].txt.~TextLabel();
			case Element::Type::Form:
				_Elements[id].frm.~Form();
			case Element::Type::Image:
				_Elements[id].img.~image();
			default:
				break;
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
				if(UI::buttons::GetPressedButton() == 1)
				{
					return OS::Events::Exit;
				}
			default:
				break;
			}
		}
	}

    //=============================================================================================================================================================

	

}




//=============================================================================================================================================================


#endif