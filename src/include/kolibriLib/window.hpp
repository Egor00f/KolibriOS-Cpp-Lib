#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>
#include <map>

#include <sys/ksys.h>

#include "os.hpp"
#include "mouse.hpp"
#include "windowBase.hpp"
#include "button.hpp"
#include "text.hpp"
#include "form.hpp"
#include "image.hpp"
#include "thread.hpp"
#include "color.hpp"

namespace KolibriLib
{ //=============================================================================================================================================================

	

	/// \brief Работа с окном
	namespace window
	{

		enum class ElementType
		{
			Button,
			TextLabel,
			form,
			image
		};

		/// @brief Структура хранящая элемент окна,
		struct Element
		{
			/// @brief Тип используемого типа
			ElementType type;
			union
			{
				UI::buttons::Button btn;
				UI::text::TextLabel txt;
				UI::Form frm;
				UI::Images::image img;
			};
			/// @brief Используется ли этот эелемент
			bool use;

			/// @brief Конструктор
			/// @param t Используемый тип
			Element(ElementType t)
			{
				type = t;
				use = false;
			}
			~Element()
			{
				switch (type)
				{
				case ElementType::Button:
					btn.~Button();
					break;
				case ElementType::TextLabel:
					txt.~TextLabel();
				default:
					break;
				}
			}
		};

		

		/// @brief Класс для работы с окном
		class Window
		{
		private:

			// Я тут теряюсь, использовать std::vector или std::list ?

			/// @brief Список всех текстовых кнопок этого окна
			std::vector<Element> _ElementList;
			

			/// @brief Заголовок окна
			std::string _title;

			/// @brief Цвета окна
			ksys_colors_table_t _colors;

			/// @brief Размеры окна
			point<unsigned> _size;

			/// @brief Номер активной формы
			/// @paragraph Активной может быть только одна форма
			unsigned ActiveForm = 0;

			/// @brief отступы от края окна
			unsigned _MARGIN;

			/// @brief Стиль окна
			int _style;

			/// @brief Окно перерисовывается сейчас (да/нет)
			bool _Redraw = false;

			
			/// @brief Добавить в список новую кнопку
			/// @param btn кнопка
			/// @return номер в списке @link _ElementList
			unsigned AddNewButton(const UI::buttons::Button& btn);

			/// @brief Добавить в список новую текствую метку
			/// @param text текстовая метка
			/// @return номер в списке @link _ElementList
			unsigned AddNewTextLabel(const UI::text::TextLabel& text);

			/// @brief Добавить форму
			/// @param form Форма
			/// @return номер в списке @link _Forms
			unsigned AddNewForm(const UI::Form& form);

			/// @brief Добавить в список изображение
			unsigned AddNewImage(const UI::Images::image &img);

			public:

			/// @brief Указатель того что нужно заканчивать выполнение потока этого окна
			bool _Exit;

			/// @brief Конструктор
			/// @param Title Заголовок окна
			/// @param size Размер окна
			/// @param style стиль окна
			/// @param colors Цвет окна
			/// @param Margin Отступы
			Window(std::string Title = "Window", point<unsigned> size = DefaultWindowSize, int style = 0x14, ksys_colors_table_t colors = Color::DefaultColorTable, unsigned Margin = 0);
			~Window();

			/// @brief Отрисовать окно
			void Render();

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin();

			/// @brief Получить размер окна
			/// @return @link _size
			point<unsigned> GetSize();

			/// @brief Изменить рамер окна
			/// @param size новый размер окна
			void SetSize(point<unsigned> size);

			/// @brief Задать стандартные цвета окна
			/// @param colorTable таблица цветов
			void SetWindowColors(const ksys_colors_table_t& colorTable);

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
			void DrawWindow(point<unsigned> coord);

			/// @brief Изменить окно
			/// @param coord позиция
			/// @param size размер
			void ChangeWindow(point<unsigned> coord, point<unsigned> size);

			/// @brief Изменить заголовок окна
			/// @param newTitle новый заголовок
			void ChangeTilte(std::string newTitle);

			/// @brief Получить размер окна
			/// @return point.x - ширина окна,
			/// @return point.y - высота окна
			point<unsigned> GetWindowSize();

			/// @brief 
			/// @return 
			std::string GetTitle();


			/// @brief Создать кнопку
			/// @param coord координата кнопки
			/// @param size размеры кнопки
			/// @param margin Отступы границ кноки от текста
			/// @param UseWindowColors Использовать ли цвет окна(да/нет)
			/// @param color Цвет кнопки
			/// @param TextColor Цвет текста кнопки
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(point<int> coord = {0, 0}, point<unsigned> size = {16, 16}, std::string Text = "Button", unsigned margin = UI::DefaultMargin, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_button);

			/// @brief Создать кнопку
			/// @param coord координата кнопки
			/// @param size размеры кнопки
			/// @param margin Отступы границ кноки от текста
			/// @param UseWindowColors Использовать ли цвет окна(да/нет)
			/// @param color Цвет кнопки
			/// @param TextColor Цвет текста кнопки
			/// @return номер кнопки в списке @link _Buttons
			unsigned CreateButton(point<int> coord = {0, 0}, point<unsigned> size = {16, 16}, UI::Images::image Image, unsigned margin = UI::DefaultMargin, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_button);

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
			unsigned CreateText(point<unsigned> coord = {0, 0}, point<unsigned> size = {16, 16}, std::string text = "Text", unsigned FontSize = 9, bool UseWindowColors = true, ksys_color_t color = OS::sys_color_table.work_text);

			/// @brief Создать текст в окне
			/// @param text текст
			/// @returnНомер текста в списке @link _Texts
			unsigned CreateText(const UI::text::TextLabel& text);

			/// @brief Удалить текст
			/// @param id Номер текста в списке @link _Texts
			void DeleteText(unsigned id);

			/// @brief Создать форму
			/// @param coord координат формы
			/// @param size Рамеры формы
			/// @return номер в списке @link _Forms
			unsigned CreateForm(point<unsigned> coord = {0, 0}, point<unsigned> size = {32, 16}, std::string BackgroundText = " ", ksys_color_t FormColor = OS::sys_color_table.work_text, ksys_color_t BackgroundTextColor = OS::sys_color_table.work_button_text);

			/// @brief Создать форму
			/// @param form форма
			/// @return номер в списке @link _Forms
			unsigned CreateForm(const UI::Form& form);

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

		unsigned Window::AddNewButton(const UI::buttons::Button& btn)
		{
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (!_ElementList[i].use)
				{
					_ElementList[i].type = ElementType::Button;
					if(btn.GetType() == UI::buttons::ContentType::Image)
					{
						_ElementList[i].btn.init(btn.GetCoord(), btn.GetSize(), btn.GetImage());
					}
					else if (btn.GetType() == UI::buttons::ContentType::Text)
					{
						_ElementList[i].btn.init(btn.GetCoord(), btn.GetSize(), btn.GetTextLabel());
					}

					_ElementList[i].btn.Activate();
					
					_ElementList[i].use = true;
					return i;
				}
			}
			Element a(ElementType::Button);

			if (btn.GetType() == UI::buttons::ContentType::Image)
			{
				a.btn.init(btn.GetCoord(), btn.GetSize(), btn.GetImage());
			}
			else if (btn.GetType() == UI::buttons::ContentType::Text)
			{
				a.btn.init(btn.GetCoord(), btn.GetSize(), btn.GetTextLabel());
			}
			a.use = true;

			_ElementList.push_back(a);
			return _ElementList.size() - 1;
        }

		unsigned Window::AddNewTextLabel(const UI::text::TextLabel& text)
        {
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (!_ElementList[i].use)
				{
					_ElementList[i].txt = text;
					_ElementList[i].type = ElementType::TextLabel;
					_ElementList[i].use = true;
					return i;
				}
			}
			Element a(ElementType::TextLabel);

			a.txt = text;
			a.use = true;
			_ElementList.push_back(a);
		}

        unsigned Window::AddNewForm(const UI::Form& form)
        {
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (!_ElementList[i].use)
				{
					_ElementList[i].type = ElementType::form;
					_ElementList[i].frm = form;
					_ElementList[i].use = true;
					return i;
				}
			}
			Element a(ElementType::form);
			a.frm = form;
			a.use = true;
			_ElementList.push_back(a);
			return _ElementList.size();
		}

		unsigned Window::AddNewImage(const UI::Images::image &img)
		{
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (!_ElementList[i].use)
				{
					_ElementList[i].type = ElementType::image;
					_ElementList[i].img = img;
					
					_ElementList[i].use = true;
					return i;
				}
			}
			Element a(ElementType::image);
			a.img = img;
			a.use = true;
			_ElementList.push_back(a);
			return _ElementList.size();
		}

    	std::string Window::GetTitle()
        {
            return _title;
        }

        Window::Window(std::string Title, point<unsigned> size, int style, ksys_colors_table_t colors, unsigned Margin)
        {
			_title = Title;
			_size = size;
			_style = style;
			_MARGIN = Margin;
			if (Color::ComparisonColorsTables(colors, Color::DefaultColorTable))
			{
				_colors = OS::GetSystemColors();
			}
			else
			{
				_colors = colors;
			}
			

			_ElementList.reserve(4 * sizeof(Element));		//Зарезервировано на всякий случай

			{
				Element a(ElementType::TextLabel);
				a.use = false;
				_ElementList.push_back(a);
			}

			DrawWindow(DefaultWindowCoord);
			_Exit = false;
		}

		Window::~Window()
		{
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (_ElementList[i].use)
				{
					_ElementList[i].btn.~Button();
					_ElementList[i].frm.~Form();
					_ElementList[i].img.~image();
					_ElementList[i].txt.~TextLabel();
				}
			}
			
		}

		void Window::SetWindowColors(const ksys_colors_table_t& colorTable)
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

		void Window::DrawWindow(point<unsigned> coord)
		{
			_ksys_create_window(coord.x, coord.y, _size.x, _size.y, _title.c_str(), _colors.work_area, _style);
		}

		void Window::ChangeWindow(point<unsigned> coord, point<unsigned> size)
		{
			_size = size;
			_ksys_change_window(coord.x, coord.y, size.x, size.y);
		}

		void Window::ChangeTilte(std::string newTitle)
		{
			_ksys_set_window_title(newTitle.c_str());
		}

		point<unsigned> Window::GetWindowSize()
		{
			return _size;
		}
		void Window::Render()
		{
			StartRedraw();
			DrawWindow(mouse::GetMousePositionOnSreen());

			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (_ElementList[i].use)
				{
					switch (_ElementList[i].type)
					{
					case ElementType::Button:
						_ElementList[i].btn.Render();
						break;
					case ElementType::TextLabel:
						_ElementList[i].txt.Render();
						break;
					case ElementType::form:
						_ElementList[i].img.Render();
						break;
					case ElementType::image:
						_ElementList[i].img.Render();
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

		point<unsigned> Window::GetSize()
		{
            return _size;
        }

		void Window::SetSize(point<unsigned> size)
		{
			_size = size;
        }

		unsigned Window::CreateButton(point<int> coord, point<unsigned> size, std::string Text, unsigned margin, bool UseWindowColors, ksys_color_t color)
		{
			if(UseWindowColors)
			{
				color = _colors.work_button;
			}
			UI::buttons::Button btn(coord, size, margin, color);
			btn.init(coord, size, Text, _MARGIN, color);
			unsigned a = AddNewButton(btn);
			btn.Deactivate();
			return a;
		}
		unsigned Window::CreateButton(point<int> coord, point<unsigned> size, unsigned margin, bool UseWindowColors, ksys_color_t color)
		{
			if (UseWindowColors)
			{
				color = _colors.work_button;
			}
			UI::buttons::Button a(coord, size, margin, color);
			a.init(coord, size, " ", _MARGIN, color);
			unsigned b = AddNewButton(a);
			a.Deactivate();
			return b;
		}
		unsigned Window::CreateButton(point<int> coord, point<unsigned> size, UI::Images::image img, unsigned margin, bool UseWindowColors, ksys_color_t color)
		{
			if (UseWindowColors)
			{
				color = _colors.work_button;
			}
			UI::buttons::Button btn(coord, size, margin, color);
			btn.init(coord, size, img, _MARGIN, color);
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
			_ElementList[id].btn.Deactivate();
			_ElementList[id].use = false;
		}
		unsigned Window::CreateText(point<unsigned> coord, point<unsigned> size, std::string text, unsigned FontSize, bool UseWindowColors, ksys_color_t color)
		{
            if(UseWindowColors)
			{
				color = _colors.work_text;
			}

			UI::text::TextLabel t(coord, size, text, FontSize);

			return AddNewTextLabel(t);
			
        }
        unsigned Window::CreateText (const UI::text::TextLabel& text)
        {
            return AddNewTextLabel(text);
        }

        void Window::DeleteText(unsigned id)
        {
			_ElementList[id].use = false;
		}

		unsigned Window::CreateForm(point<unsigned> coord, point<unsigned> size, std::string BackgroundText, ksys_color_t FormColor, ksys_color_t BackgroundTextColor)
		{
			UI::Form form (coord, size, BackgroundText, FormColor, BackgroundTextColor, _MARGIN);
			return AddNewForm (form);
		}

		unsigned Window::CreateForm (const UI::Form& form)
		{
            return AddNewForm(form);
        }

        std::string Window::GetTextFromForm(unsigned form)
        {
			return _ElementList[form].frm.GetInput();
		}
		
        void Window::DeleteForm(unsigned id)
        {
			_ElementList[id].use = false;
		}

        void Window::FormHandler()
        {
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if (_ElementList[i].use) // Если форма используется
				{
					if (_ElementList[i].type == ElementType::form)
					{
						if (_ElementList[i].frm.ButtonHandler())
						{
							ActiveForm = i;
						}
					}
				}
			}
			_ElementList[ActiveForm].frm.Handler();
		}

        unsigned Window::Handler()
		{
			unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент, и идём дальше

			switch (Event)
			{
			case KSYS_EVENT_REDRAW:
				Render();
				break;
			case KSYS_EVENT_BUTTON:
				for (unsigned i = 0; i < _ElementList.size(); i++)
				{
					if (_ElementList[i].use) // Если кнопка используется
					{
						if (_ElementList[i].type == ElementType::Button)
							_ElementList[i].btn.Handler();
					}
				}
				FormHandler();
				
				unsigned button = KolibriLib::UI::buttons::GetPressedButton();
				if (button == 1)
				{
					_Exit = true;
				}
				
				break;
			}

			point<int> mouse = mouse::GetMousePositionInWindow();

			if ((mouse.x < _size.x + 4 || mouse.x > _size.x - 4) && (mouse.y > 0 || mouse.y < _size.y))
			{
				mouse::SetCursor(mouse::Cursor.horz);
			}
			else if ((mouse.x < 0 + 4 || mouse.x > 0 - 4) && (mouse.y > 0 || mouse.y < _size.y))
			{
				mouse::SetCursor(mouse::Cursor.horz);
			}
			else
			{
				mouse::SetCursor(mouse::Cursor.pointer);
			}

			return Event;
		}
		unsigned Window::GetPressedButton()
		{
			for (unsigned i = 0; i < _ElementList.size(); i++)
			{
				if(_ElementList[i].use)
				{
					if ((_ElementList[i].type == ElementType::Button) && _ElementList[i].btn.GetStatus())
					{
						return i;
					}
				}
			}
			return _ElementList.size();
		}
	}

    //=============================================================================================================================================================

}




//=============================================================================================================================================================


#endif