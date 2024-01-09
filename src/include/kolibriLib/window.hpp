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

	

	/// \brief Работа с окном
	namespace window
	{
		
		struct ButtonListElement
		{
			UI::buttons::Button btn;
			bool use;
		};
		
		struct TextListElement
		{
			UI::text::TextLabel txt;
			bool use;
		};

		struct FormListElement
		{
			UI::Form frm;
			bool use;
		};

		/// @brief Класс для работы с окном
		class Window
		{
		private:
			/// @brief Заголовок окна
			std::string _title;

			/// @brief Размеры окна
			point _size;

			/// @brief Цвета окна
			ksys_colors_table_t _colors;

			/// @brief отступы от края окна
			unsigned _MARGIN;

			/// @brief Окно перерисовывается сейчас (да/нет)
			bool _Redraw = false;

			/// @brief Стиль окна
			int _style;

			// Я тут теряюсь, использовать std::vector или std::list ?

			/// @brief Список всех кнопок этого окна
			std::vector<ButtonListElement> _Buttons;
			
			/// @brief список всех TextLabel
			std::vector<TextListElement> _Texts;

			/// @brief Список всех форм
			std::vector<FormListElement> _Forms;
			/// @brief Номер активной формы
			/// @paragraph Активной может быть только одна форма
			unsigned ActiveForm = 0;

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
			Window(std::string Title = "Window", point size = DefaultWindowSize, int style = 0x14, ksys_colors_table_t colors = Color::DefaultColorTable, unsigned Margin = 0);
			~Window();

			/// @brief Отрисовать окно
			void Render();

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin();

			/// @brief Получить размер окна
			/// @return @link _size
			point GetSize();

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
			void DrawWindow(point coord = mouse::GetMousePositionOnSreen());

			/// @brief Изменить окно
			/// @param coord позиция
			/// @param size размер
			void ChangeWindow(point coord, point size);

			/// @brief Изменить заголовок окна
			/// @param newTitle новый заголовок
			void ChangeTilte(std::string newTitle);

			/// @brief Получить размер окна
			/// @return point.x - ширина окна,
			/// @return point.y - высота окна
			point GetWindowSize();

			/// @brief Создать кнопку
			/// @param coord координата кнопки
			/// @param size размеры кнопки
			/// @param Text текст кнопки
			/// @param margin Отступы границ кноки от текста
			/// @param UseWindowColors Использовать ли цвет окна(да/нет)
			/// @param color Цвет кнопки
			/// @param TextColor Цвет текста кнопки
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(point coord = {0, 0}, point size = {16, 16}, std::string Text = " ", unsigned margin = UI::DefaultMargin, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_button, ksys_color_t TextColor = OS::sys_color_table.work_button_text);

			/// @brief Создать кнопку
			/// @param btn кнопка
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(UI::buttons::Button btn);

			/// @brief Удалить кнопку
			/// @param id номер удаляемой кнопки
			void DeleteButton(unsigned id);

			/// @brief Создать текст в окне
			/// @param coord координата текста
			/// @param size рамер рамок текста
			/// @param text Сам текст
			/// @param FontSize Рамер текста
			/// @param UseWindowColors Использовать цвета окна(да/нет)
			/// @param color Цвет текста
			/// @return Номер текста в списке @link _Texts
			unsigned CreateText(point coord = {0,0}, point size = {16, 16}, std::string text = "Text", unsigned FontSize = 9, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_text);

			/// @brief Создать текст в окне
			/// @param text текст
			/// @returnНомер текста в списке @link _Texts
			unsigned CreateText(UI::text::TextLabel text);

			/// @brief Удалить текст
			/// @param id Номер текста в списке @link _Texts
			void DeleteText(unsigned id);

			/// @brief Создать форму
			/// @param coord координат формы
			/// @param size Рамеры формы
			/// @return номер в списке @link _Forms
			unsigned CreateForm(point coord = {0, 0}, point size = {32, 16}, std::string BackgroundText = " ", ksys_color_t FormColor = OS::sys_color_table.work_text, ksys_color_t BackgroundTextColor = OS::sys_color_table.work_button_text);

			/// @brief Создать форму
			/// @param form форма
			/// @return номер в списке @link _Forms
			unsigned CreateForm(UI::Form form);

			/// @brief Получить текст из формы
			/// @param form номер формы
			/// @return текст введённый пользователем в эту форму
			std::string GetTextFromForm(unsigned form);

			/// @brief Удалить форму
			/// @param id номер формы в списке @link _Forms
			void DeleteForm(unsigned id);

			/// @brief Обработчик форм
			void FormHandler();

			/// @brief Обработчик элементов
			/// @return Ивент окна
			unsigned Handler();

			/// @brief Получить нажатую кнопку
			/// @return Номер нажатой кнопки
			unsigned GetPressedButton();
		};

		unsigned Window::AddNewButton(UI::buttons::Button btn)
		{
            for(unsigned i = 0; i < _Buttons.size(); i++)
			{
				if(!_Buttons[i].use)
				{
					_Buttons[i].btn = btn;
					_Buttons[i].btn.Activate();
					_Buttons[i].use = true;
					return i;
				}
			}
			ButtonListElement a;
			a.btn = btn;
			a.use = true;
			_Buttons.push_back(a);
			return _Buttons.size();
		}

        unsigned Window::AddNewTextLabel(UI::text::TextLabel text)
        {
			for (unsigned i = 0; i < _Texts.size(); i++)
			{
				if (!_Texts[i].use)
				{
					_Texts[i].txt = text;
					_Texts[i].use = true;
					return i;
				}
			}
			TextListElement a;
			a.txt = text;
			a.use = true;
			_Texts.push_back(a);
		}

        unsigned Window::AddNewForm(UI::Form form)
        {
			for (unsigned i = 0; i < _Forms.size(); i++)
			{
				if (!_Forms[i].use)
				{
					_Forms[i].frm = form;
					_Forms[i].use = true;
					return i;
				}
			}
			FormListElement a;
			a.frm = form;
			a.use = true;
			_Forms.push_back(a);
			return _Forms.size();
		}

        Window::Window(std::string Title, point size, int style, ksys_colors_table_t colors, unsigned Margin)
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
			_Texts.reserve(8 * sizeof(TextListElement));
			_Buttons.reserve(8 * sizeof(ButtonListElement));
			_Forms.reserve(8 * sizeof(FormListElement));
			DrawWindow(DefaultWindowCoord);
			Render();
		}

		Window::~Window()
		{
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

		void Window::DrawWindow(point coord)
		{
			_ksys_create_window(coord.x, coord.y, _size.x, _size.y, _title.c_str(), _colors.work_area, _style);
		}

		void Window::ChangeWindow(point coord, point size)
		{
			_size = size;
			_ksys_change_window(coord.x, coord.y, size.x, size.y);
		}

		void Window::ChangeTilte(std::string newTitle)
		{
			_ksys_set_window_title(newTitle.c_str());
		}

		point Window::GetWindowSize()
		{
			return _size;
		}
		void Window::Render()
		{
			StartRedraw();
			DrawWindow();

			for(unsigned i = 0; i < _Buttons.size(); i++)
			{
				if(_Buttons[i].use)
				{
					_Buttons[i].btn.render();
				}
			}
			for(unsigned i = 0; i < _Texts.size(); i++)
			{
				if(_Texts[i].use)
				{
					_Texts[i].txt.render();
				}
			}
			for(unsigned i = 0; i < _Forms.size(); i++)
			{
				if(_Forms[i].use)
				{
					_Forms[i].frm.render();
				}
			}

			EndRedraw();
		}

        unsigned Window::GetMargin()
        {
            return _MARGIN;
        }

        point Window::GetSize()
        {
            return _size;
        }

        unsigned Window::CreateButton(point coord, point size, std::string Text, unsigned margin, bool UseWindowColors, ksys_color_t color, ksys_color_t TextColor)
		{
			if(UseWindowColors)
			{
				color		= _colors.work_button;
				TextColor	= _colors.work_button_text;
			}
			UI::buttons::Button btn(coord, size, Text, margin, color, TextColor);
			unsigned a = AddNewButton(btn);
			btn.Deactivate();
			return a;
		}

        unsigned Window::CreateButton(UI::buttons::Button btn)
        {
            return AddNewButton(btn);
        }

        void Window::DeleteButton(unsigned id)
        {
			_Buttons[id].btn.Deactivate();
			_Buttons[id].use = false;
		}
        unsigned Window::CreateText(point coord, point size, std::string text, unsigned FontSize, bool UseWindowColors, ksys_color_t color)
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

        void Window::DeleteText(unsigned id)
        {
			_Texts[id].use = false;
        }

		unsigned Window::CreateForm (point coord, point size, std::string BackgroundText, ksys_color_t FormColor, ksys_color_t BackgroundTextColor)
		{
			UI::Form form (coord, size, BackgroundText, FormColor, BackgroundTextColor, _MARGIN);
			return AddNewForm (form);
		}

		unsigned Window::CreateForm (UI::Form form)
		{
            return AddNewForm(form);
        }

        std::string Window::GetTextFromForm(unsigned form)
        {
            return _Forms[form].frm.GetInput();
        }
		
        void Window::DeleteForm(unsigned id)
        {
			_Forms[id].use = false;
        }

        void Window::FormHandler()
        {
			for (unsigned i = 0; i < _Forms.size(); i++)
			{
				if (_Forms[i].use) // Если форма используется
				{
					if (_Forms[i].frm.ButtonHandler())
					{
						ActiveForm = i;
					}
				}
			}
			_Forms[ActiveForm].frm.Handler();
		}

        unsigned Window::Handler()
		{
			unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент

			switch (Event)
			{
			case KSYS_EVENT_REDRAW:
				Render();
				break;
			case KSYS_EVENT_BUTTON:
				for (unsigned i = 0; i < _Buttons.size(); i++)
				{
					if (_Buttons[i].use) // Если кнопка используется
					{
						_Buttons[i].btn.Handler();
					}
				}
				FormHandler();


				
				unsigned button = KolibriLib::UI::buttons::GetPressedButton();
				if (button == 1)
				{
					EXIT = true;
					EXITCODE = 0;
				}
				
				break;
			}
			return Event;
		}
		unsigned Window::GetPressedButton()
		{
			for(unsigned i = 0; i < _Buttons.size(); i++)
			{
				if(_Buttons[i].btn.GetStatus())
				{
					return i;
				}
			}
			return _Buttons.size();
		}
	}

    //=============================================================================================================================================================

}




//=============================================================================================================================================================


#endif