#ifndef __OS_H__
#define __OS_H__

#include <string.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/color.hpp>

namespace KolibriLib
{
	/// @brief Работа с системой
	namespace OS
	{

		/// @brief Таблица стандартных(системных) цветов
		Colors::ColorsTable sys_color_table;

		/// @brief Получить системные цвета
		/// @paragraph Функция изменяет переменную @link sys_color_table
		/// @return Таблица системных цветов
		Colors::ColorsTable GetSystemColors();

		/// @brief Ивент
		typedef unsigned int Event;

		enum Events
		{
			/// @brief Ивента небыло
			None    = KSYS_EVENT_NONE,
			/// @brief Перересовка окна
			Redraw  = KSYS_EVENT_REDRAW,
			/// @brief Нажата кнопка
			Button  = KSYS_EVENT_BUTTON,
			/// @brief Активность мыши
			Mouse   = KSYS_EVENT_MOUSE,
			/// @brief Активность со стороны клавиатуры
			Key     = KSYS_EVENT_KEY,
			/// @brief 
			Desktop = KSYS_EVENT_DESKTOP,
			Debug   = KSYS_EVENT_DEBUG,
			/// @brief Выход
			/// @paragraph Означает что пользователь нажал кнопку X
			Exit
		};

		/// \brief Ждать ивента
		/// \return Ивент
		inline Event WaitEvent()
		{
			return _ksys_wait_event();
		}

		/// \brief Ждать ивента
		/// \param Таймаут (в 1/100 секунды), время сколько ждать
		/// \return Ивент
		Event WaitEvent(uint32_t TimeOut = 0);

		/// \brief Проверить пришёл ли ли ивент
		/// \return Ивент
		inline Event CheckEvent()
		{
			return _ksys_check_event();
		}

		/// \brief Запустить программу
		/// \param AppName Полное имя исполняемого файла
		/// \param args аргументы. Максимум 256 символов
		/// \return > 0 - программа загружена, eax содержит PID, < 0 если исполняемы файл не найден
		int Exec(const filesystem::Path& AppName, const std::string& args);


		typedef ksys_time_t Time;
		/// @brief Получить системное время
		/// @return
		inline Time GetTime()
		{
			return _ksys_get_time();
		}

		/// @brief Получить состояние спикера(Вкл/выкл)
		/// @return true если спикер разрешён, иначе false
		inline bool SpeakerStatus()
		{
			bool a;
			asm_inline(
				"int $0x40"
				: "=a"(a)
				: "a"(18), "b"(8), "c"(1)
			);
			return !a;
		}

		/// @brief Переключить состояние спикера
		inline void SpeakerSwitch()
		{
			asm_inline(
				"int $0x40" 
				::"a"(18), "b"(8), "c"(2)
			);
		}

		/// @brief получить кол-во свободной памяти
		/// @return размер свободной памяти в килобайтах
		inline std::size_t FreeMem()
		{
			std::size_t a;
			asm_inline(
				"int $0x40"
				: "=a"(a)
				: "a"(18), "b"(16)
			);
			return a;
		}

		/// @brief Получить кол-во всей памяти
		/// @return Размер всей памяти в килобайтах
		inline std::size_t AllMem()
		{
			std::size_t a;
			asm_inline(
				"int $0x40"
				: "=a"(a)
				: "a"(18), "b"(17)
			);
			return a;
		}

		/// @brief Список языков системы
		/// @paragraph PS жаль что так мало языков поддерживается...
		enum lang
		{
			/// @brief Английский 
			Eng = 0,
			/// @brief Финский
			Fi,
			/// @brief Немецкий
			Ger,
			/// @brief Русский
			Rus
		};

		/// @brief Получить язык системы
		/// @return Занечение из списка @link lang
		inline int GetLang()
		{
			int a;
			asm_inline(
				"int $0x40"
				: "=a"(a)
				: "a"(26), "b"(5)
			);
			return a;
		}

	} // namespace OS

	/// \brief Подождать
	/// \param time время задержки(в 1/100 секунды)
	/// @paragraph Функция просто ждёт, ничего не делает
	void Wait(int time = -1);

} // namespace KolibriLib


#endif // __OS_H__