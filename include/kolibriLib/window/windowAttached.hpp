#ifndef __WINDOWATTACHED_H__
#define __WINDOWATTACHED_H__

#include <kolibriLib/window/window.hpp>
namespace KolibriLib
{
	namespace window
	{
		/// @brief Окно что запускается в отдельном потоке
		/// @details А нафига оно нужно? Знаете, меня всегда бесило когда приложения зависают, а окошко нельзя потербонькать
		class WindowAttached
		{
			public:
				WindowAttached(const Window_t &window);

				~WindowAttached();

				/// @brief Полная перересовка окна
				void Redraw();

				/// @brief Отрисовать окно
				void Render();

				/// @brief Получить размер окна
				/// @return _size
				UDim GetSize() const;

				/// @brief Получить координаты окна
				/// @return
				UDim GetCoord() const;

				void SetSize(const UDim &NewSize);

				/// @brief
				/// @param NewCoord
				void SetCoord(const UDim &NewCoord);

				void SetSize(const Size &NewSize);

				/// @brief
				/// @param NewCoord
				void SetCoord(const Coord &NewCoord);

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

				/// @brief Обработчик окна
				/// @return Ивент
				OS::Event Handler();

				/// @brief Проверить какая нажата
				UI::buttons::ButtonID GetPressedButton();

				template <class T>
				/// @brief Добавить UI элемент
				/// @param element
				/// @return std::pair<номер элемента в списке, указатель на элемент>
				T *AddElement(const T &element);

				template <class T>
				bool DeleteElement(T *element);

				/// @brief Снять фокус с этого окна
				void Unfocus() const;

				/// @brief Поставить фокус на это окно
				void Focus() const;

				/// @brief Отрисовать все элементы
				void RenderAllElements() const;

				/// @brief Изменить позицию окна относительно одних
				/// @param
				void SetPosition(const Pos &position);

				/// @brief Получить позицию окна относительно одних
				/// @return
				Pos GetPosition() const;

				UI::buttons::ButtonsIDController *GetButtonIDController() const;

				void SetButtonIDController(const UI::buttons::ButtonsIDController *buttonsIDController);

			private:
				Window *_wndw;
		};

		
	} // namespace window
	
} // namespace KolibriLib




#endif // __WINDOWATTACHED_H__