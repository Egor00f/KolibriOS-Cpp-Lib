#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__


#include <string>
#include <vector>
#include <type_traits>


#include <sys/ksys.h>

#include "types.hpp"
#include "input.hpp"
#include "os.hpp"
#include "windowBase.hpp"
#include "button.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "form.hpp"
#include "frame.hpp"
#include "menu.hpp"
#include "screen.hpp"

namespace KolibriLib
{ 



	/// \brief Работа с окном
	namespace window
	{




		/// @brief Класс для работы с окном
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
				unsigned DrawPrioritet;
				bool use;

				Element();
				~Element();

				template <class T>
				void SetElement(const T& elem);

				void free();
			};

			/// @brief Заголовок окна
			std::string _title;

			/// @brief Список всех кнопок этого окна
			std::vector<Element> _Elements;

			/// @brief Размеры окна
			UI::Size _size;

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


			/// @brief Добавить в список новую кнопку
			/// @param btn кнопка
			/// @return номер в списке @link _Buttons
			unsigned AddNewButton(const UI::buttons::Button& btn);

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
			Window(const std::string &Title = "Window", const UI::Size &size = DefaultWindowSize, const Colors::ColorsTable &colors = Colors::DefaultColorTable, const Colors::Color &TitleColor = OS::sys_color_table.work_text, bool Resize = false, bool RealtimeReadraw = false, bool Gradient = false, unsigned Transparency = 0, const unsigned &Margin = 0);
			~Window();

			/// @brief Полная перересовка окна
			void Redraw();

			/// @brief Отрисовать окно
			void Render(UI::Coord coord = DefaultWindowCoord);

			/// @brief Получить рамер отступов в этом окне
			/// @return @link _MARGIN
			unsigned GetMargin();

			/// @brief Получить размер окна
			/// @return @link _size
			UI::Size GetSize();

			/// @brief Задать стандартные цвета окна
			/// @param colorTable таблица цветов
			void SetWindowColors(const Colors::ColorsTable& colorTable);

			/// @brief Начать перересовку окна
			/// @paragraph Стирает всё что было нарисованно в окне
			/// @paragraph Обязательно после должна быть вызвана функция #EndRedraw()
			void StartRedraw();

			/// @brief Закончить перересовку окна
			/// @paragraph Обязательно после должна быть вызвана функция #StartRedraw()
			void EndRedraw();

			/// @brief Получить координаты окна
			/// @return 
			const UI::Coord& GetCoord() const;

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
			void ChangeTilte(const std::string& newTitle);

			/// @brief Получить размер окна
			/// @return point.x - ширина окна,
			/// @return point.y - высота окна
			UI::Size GetWindowSize();

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

			template <class T>
			/// @brief Добавить UI элемент
			/// @param element
			unsigned AddElement(const T &element);

			template <class T>
			/// @brief Изменить элемент
			/// tparam T
			/// @param i
			/// @param element
			void SetElement(unsigned i, const T& element);

			/// @brief
			/// @tparam T
			/// @param i
			/// @return
			template <class T>
			T GetElement(unsigned i) const;

			/// @brief Снять фокус с этого окна
			void Unfocus() const;
			/// @brief Поставить фокус на это окно
			void Focus() const;
		};
	}

    //=============================================================================================================================================================



}




//=============================================================================================================================================================


#endif
