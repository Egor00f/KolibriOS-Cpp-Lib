#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <sys/ksys.h>

#include <stdlib.h>
#include <string>
#include <utility>
#include <algorithm>
#include <type_traits>


#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <input.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <UI.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/graphic/background.hpp>
#include <kolibriLib/globals.hpp>

namespace KolibriLib
{

	/// \brief Работа с окном
	namespace window
	{
		/// @brief просто класс полями для Window
		class Window_t: public UI::GuiObject
		{
		public:
			Window_t(const std::string &Title = "Window", const Colors::ColorsTable &colors = Globals::SystemColors, bool Resize = false, bool RealtimeReadraw = false, bool Gradient = false, unsigned Transparency = 0, const unsigned &Margin = UI::DefaultMargin);

		protected:
			/// @brief Заголовок окна
			std::string _title;

			/// @brief Список всех кнопок этого окна
			std::vector<UIElement*> _Elements;

			UI::buttons::ButtonsIDController _buttonsController;

			/// @brief Цвета окна
			Colors::ColorsTable _colors;

			/// @brief Последняя нажатая кнопка
			UI::buttons::ButtonID _PressedButton = UI::buttons::ButtonIDNotSet;

			/// @brief Стиль окна
			uint8_t _style;

			/// @brief Прозрачность окна
			uint8_t _Transparency;
			
			/// @brief Окно перерисовывается сейчас (да/нет)
			mutable bool _Redraw = false;

			/// @brief Окно пересовывается при перетаскивании
			bool _RealtimeRedraw;
		};

		/// @brief Класс для работы с окном
		/// @paragraph По простому: Окно остаётся привязаным к потоку, в которм бы вызван конструктор. Если вызывать методы из других потоков, то вести они себя будут неадекватно
		/// @example example.cpp
		/// @example checkboxExample.cpp
		class Window: public Window_t
		{
		public:

			/// @brief Конструктор
			/// @param Title Заголовок окна
			/// @param size Размер окна
			/// @param style стиль окна
			/// @param colors Цвет окна
			/// @param Margin Отступы
			Window(const std::string &Title = "Window", const Size &size = DefaultWindowSize, const Coord &coord = DefaultWindowCoord, const Colors::ColorsTable &colors = Globals::SystemColors, bool Resize = false, bool RealtimeReadraw = false, bool Gradient = false, unsigned Transparency = 0, Pos position = Pos::Normal, const unsigned &Margin = UI::DefaultMargin);

			/// @brief Конструктор, необходим только для windowAttached
			Window(const Window_t &wndw);

			~Window();

			/// @brief Полная перересовка окна
			void Redraw();

			/// @brief Отрисовать окно
			void Render();

			/// @brief Получить размер окна
			/// @return _size
			UDim GetSize() const override;

			/// @brief Получить координаты окна
			/// @return
			UDim GetCoord() const override;

			void SetSize(const UDim &NewSize) override;

			/// @brief 
			/// @param NewCoord 
			void SetCoord(const UDim &NewCoord) override;

			void SetSize(const Size &NewSize) override;

			/// @brief 
			/// @param NewCoord 
			void SetCoord(const Coord &NewCoord) override;

			/// @brief Получить абсолютный размер окна
			/// @details Нужно только для классов наследуемых из UIElement
			/// @return 
			Coord GetAbsoluteCoord() const override;

			/// @brief Получить абсолютный размер окна
			/// @details Нужно только для классов наследуемых из UIElement
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
			/// @example example.cpp
			OS::Event Handler();

			/// @brief Проверить какая нажата
			/// @return ButtonID нажатой кнопки
			/// @example example.cpp
			UI::buttons::ButtonID GetPressedButton();

			/// @brief Добавить UI элемент
			/// @param element указатель на элемент
			/// @details Зачем добавлять в окно элементы ui? Да чтоб при перерисовке окна не нужнобыло отрисовывать все ручками
			/// @return указатель на элемент(новый)
			void AddElement(UIElement *element);

			template <class T>
			/// @brief Добавить UI элемент
			/// @param element сам элемент
			/// @details Зачем добавлять в окно элементы ui? Да чтоб при перерисовке окна не нужнобыло отрисовывать все ручками
			/// @return указатель на элемент(новый)
			/// @example example.cpp
			T *AddElement(const T &element);

			/// @brief Удалить элемент из окна
			template <class T >
			bool DeleteElement (T* element);

			/// @brief Снять фокус с этого окна
			void Unfocus () const;

			/// @brief Поставить фокус на это окно
			void Focus () const;

			/// @brief Отрисовать все элементы
			/// @example example.cpp
			void RenderAllElements() const;

			/// @brief Изменить позицию окна относительно одних
			/// @param
			void SetPosition(const Pos &position);

			/// @brief Получить позицию окна относительно одних
			/// @return
			Pos GetPosition() const;

			UI::buttons::ButtonsIDController* GetButtonIDController() const override;

			void SetButtonIDController(const UI::buttons::ButtonsIDController* buttonsIDController) override;
		};

		//=============================================================================================================================================================

		#ifndef __MakeStaticLib__

		template <class T>
		T* KolibriLib::window::Window::AddElement(const T &element)
		{
			PrintDebug("Add element\n");

			T *p = new T(element);

			if (p->GetParent() == nullptr)
			{
				p->WindowAsParent(this);
			}

			p->SetButtonIDController(&_buttonsController);

			_Elements.push_back((UIElement*)p);


			return p;
		}

		template<class T>
		bool Window::DeleteElement(T * element)
		{
			PrintDebug("Delete element\n");

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
		}

		#endif
	} // namespace window

}

#endif
