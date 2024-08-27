#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__

/*
	Тут тип базовый функционал работы с окном
*/

#include <sys/ksys.h>
#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>
#include <input.hpp>

namespace KolibriLib
{

	/// @brief Работа с окном
	namespace window
	{

		/// @brief Размер окна поумолчанию
		const Size DefaultWindowSize = {600, 400};

		/// @brief Соординаты окна по умолчанию
		const Coord DefaultWindowCoord = {100, 100};

		/// @brief Список стилей для окна
		enum WindowStyle
		{
			/// @brief окно фиксированных размеров
			FixSize = 0,
			
			/// @brief только определить область окна, ничего не рисовать
			NoDraw = 0b00000001,

			/// @brief окно изменяемых размеров
			CanResize = 0b00000010,

			/// @brief окно со скином
			withSkin = 0b00000011,

			/// @brief окно со скином фиксированных размеров
			FixSizewithSkin = 0b00000100,

			/// @brief у окна есть заголовок
			WindowHaveTitle = 0b00010000,

			/// @brief Координаты крафических приметивов относительно окна
			Relative = 0b00100000,

			/// @brief не закрашивать рабочую область при отрисовке окна
			NoDrawWorkspace = 0b01000000,

			/// @brief градиентная заливка рабочей области
			GradientDraw = 0b10000000
		};

		/// @brief Список констант положения окна относительно других окон:
		typedef enum Pos
		{
			/// @brief На фоне
			BackGround = -2,

			/// @brief всегда за другими окнами
			AlwaysBack = -1,

			/// @brief обчное
			Normal = 0,

			/// @brief Всегда поверх остальных окон
			AlwaysTop = 1
		} Pos;

		/// @brief
		/// @param coord Координаты окна(его левого верхнего угола) на экране
		/// @param size Размеры окна
		/// @param title Заголовок окна
		/// @param WorkColor цвет рабочей области окна
		/// @param TitleColor Цвет текста заголовка
		/// @param style Стиль
		inline void CreateWindow(const Coord &coord,
		                         const Size &size,
		                         const std::string &title,
		                         const Colors::Color &WorkColor	= OS::GetSystemColors().work_area,
		                         Colors::Color TitleColor	= OS::GetSystemColors().grab_text,
		                         uint8_t style	= WindowStyle::CanResize | WindowStyle::Relative)
		{
			_ksys_create_window(coord.x, coord.x, size.x, size.y, title.c_str(), WorkColor, style);
		}

		/// @brief Снять фокус с окна
		/// @param slot слот окна
		inline void UnfocusWindow(const Thread::Slot &slot)
		{
			_ksys_unfocus_window(slot);
		}

		/// @brief Получить размер окна
		/// @param pid PID процесса кторый создал окно
		/// @return Размер окна
		inline Size GetWindowSize(Thread::PID pid = Thread::ThisThread)
		{
			auto inf = Thread::GetThreadInfo(pid);
			return {inf.winx_size, inf.winy_size};
		}

		/// @brief Поставить фокус на окно
		/// @param slot слот окна
		inline void FocusWindow(const Thread::Slot &slot)
		{
			_ksys_focus_window(slot);
		}

		/// @brief Получить слот активного окна
		/// @return Слот активного в данный момент окна
		inline Thread::Slot GetActiveWindow()
		{
			Thread::Slot s;

			asm_inline (
				"int $0x40"
				: "=a"(s)
				: "a"(18), "b"(7)
			);
			
			return s;
		}

		/// @brief Свернуть окно
		inline void MinimizeWindow()
		{
			asm_inline (
				"int $0x40" 
				:: "a"(18), "b"(10)
			);
		}

		/// @brief Свернуть все окна
		inline void MinimizeAllWindows()
		{
			asm_inline (
				"int $0x40" 
				:: "a"(18), "b"(23)
			);
		}

		/// @brief получить координаты окна
		/// @param pid PID процесса, который создал окно
		/// @return Координаты окна
		inline Coord GetWindowCoord(Thread::PID pid = Thread::ThisThread)
		{
			auto inf = Thread::GetThreadInfo(pid);
			return {inf.winx_start, inf.winy_start};
		}

		/// @brief Получить положение окна относительно других окон
		/// @return одна из констант из списка Pos
		inline Pos GetWindowPos()
		{
			Pos a;
			asm_inline (
				"int $0x40"
				: "=a"(a)
				: "a"(18), "b"(25), "c"(1));
			return a;
		}

		/// @brief Изменить положение окна относительно дроугих окон
		/// @param pos значение из списка Pos
		/// @param pid процесс окна, по умолчанию текущий
		/// @return false если ошибка
		//// @return true если успешно
		inline bool SetWindowPos(Pos pos, Thread::PID pid = Thread::ThisThread)
		{
			bool a;
			asm_inline (
				"int $0x40"
				: "=a"(a)
				: "a"(18), "b"(25), "c"(2), "d"(pid), "S"(pos));
			return a;
		}

		/// @brief Получить высоту скина(заголовка окна)
		/// @return высота скина
		inline unsigned GetSkinHeight()
		{
			return _ksys_get_skin_height();
		}

		/// @brief Получить размер рабочей области окна
		/// @return Размер рабочей области окна
		inline Size GetWorkArea()
		{
			ksys_pos_t a, b;
			asm_inline (
				"int $0x40"
				: "=a"(a), "=b"(b)
				: "a"(48), "b"(5));
			return {a.y - a.x + 1, b.y - b.x + 1};
		}

	} // namespace window

} // namespace KolibriLib

#endif // __WINDOWBASE_H__