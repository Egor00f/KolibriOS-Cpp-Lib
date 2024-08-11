#ifndef __OS_H__
#define __OS_H__


#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/color.hpp>
#include "thread.hpp"

#include <vector>

namespace KolibriLib
{
	/// @brief Работа с системой
	namespace OS
	{

		/// @brief Получить системные цвета
		/// @return Таблица системных цветов
		Colors::ColorsTable GetSystemColors();

		/// @brief Именить системыне цвета
		/// @param Указатель на таблицу системных цветов
		inline void SetSystemColors(Colors::ColorsTable *table)
		{
			asm_inline(
				"int $0x40"
				::"a"(48), "b"(2), "c"(table), "d"(sizeof(Colors::ColorsTable))
			);
		}
		
		/// @brief Перечисление всех ивнтов
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

			/// @brief Ивент от экрана
			Desktop = KSYS_EVENT_DESKTOP,
			
			/// @brief Программу открыли в дебагере
			Debug   = KSYS_EVENT_DEBUG,

			/// @brief Выход
			Exit
		};

		/// @brief Ивент
		typedef Events Event;

		/// \brief Ждать ивента
		/// \return Ивент
		inline Event WaitEvent()
		{
			return (Event)_ksys_wait_event();
		}

		/// \brief Ждать ивента
		/// \param Таймаут (в 1/100 секунды), время сколько ждать
		/// \return Ивент
		inline Event WaitEvent(const uint32_t &TimeOut)
		{
			return (Event)_ksys_wait_event_timeout(TimeOut);
		}

		/// \brief Проверить пришёл ли ли ивент
		/// \return Ивент
		inline Event CheckEvent()
		{
			return (Event)_ksys_check_event();
		}

		/// \brief Запустить программу
		/// \param AppName Полное имя исполняемого файла
		/// \param args аргументы. Максимум 256 символов
		/// @param debug режим дебага
		/// \return PID запущенной программы
		/// @return -1 если произошла ошибка
		Thread::PID Exec(const filesystem::Path& AppName, const std::string& args, bool debug = false);

		/// @brief Время
		typedef ksys_time_bcd_t Time;

		typedef ksys_date_bcd_t Date;

		/// @brief Получить системное время
		/// @return
		inline Time GetTime()
		{
			return _ksys_get_time();
		}

		inline Date GetDate()
		{
			return _ksys_get_date();
		}

		typedef enum SetTimeOrDate
		{
			/// @brief успешно
			DONE,

			/// @brief параметр задан неверно
			WrongArgs,

			/// @brief CMOS-батарейки разрядились
			CMOS
		} SetTimeOrDate;

		/// @brief Установить системную  время
		/// @param NewTime Время что будет установленно
		inline SetTimeOrDate SetTime(Time NewTime)
		{
			SetTimeOrDate ret;

			asm_inline (
				"int $0x40" 
				: "=a"(ret)
				: "a"(22), "b"(0), "c"(NewTime)
			);
			return ret;
		}

		/// @brief Установитьсистемную  дату
		/// @param NewData Дата что будет установленна
		inline SetTimeOrDate SetDate(Date NewDate)
		{
			SetTimeOrDate ret;

			asm_inline (
				"int $0x40"
				: "=a"(ret)
				: "a"(22), "b"(1), "c"(NewDate)
			);

			return ret;
		}

		/// @brief Установить день недели
		/// @param NewDayOfWeek День недели от 1 до 7
		/// @note Ценность установки дня недели представляется сомнительной, поскольку он мало где используется(день недели можно рассчитать по дате)
		inline SetTimeOrDate SetDayOfWeek(uint8_t NewDayOfWeek)
		{
			SetTimeOrDate ret;

			asm_inline(
				"int $0x40" 
				: "=a"(ret)
				: "a"(22), "b"(2), "c"(NewDayOfWeek)
			);

			return ret;
		}

		/// @brief Установить бедильник
		/// @param AlarmTime Время будильника
		/// @paragraph Будильник можно установить на срабатывание в заданное время каждые сутки. При этом отключить его существующими системными функциями нельзя.
		/// @paragraph Срабатывание будильника заключается в генерации IRQ8.
		/// @paragraph Будильник - глобальный системный ресурс; установка будильника автоматически отменяет предыдущую установку 
		inline SetTimeOrDate SetAlarm(Time AlarmTime)
		{
			SetTimeOrDate ret;

			asm_inline(
				"int $0x40" 
				: "=a"(ret)
				: "a"(22), "b"(3), "c"(AlarmTime)
			);
			return ret;
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
		typedef enum lang
		{
			/// @brief Английский 
			Eng = 0,
			/// @brief Финский
			Fi = 1,
			/// @brief Немецкий
			Ger = 2,
			/// @brief Русский
			Rus = 3
		} lang;

		/// @brief Получить язык системы
		/// @return Занечение из списка lang
		inline lang GetLang()
		{
			int a;
			asm_inline(
				"int $0x40"
				: "=a"(a)
				: "a"(26), "b"(5)
			);
			return (lang)a;
		}

		/// @brief Иконки в сообщениях
		/// @image notify.orig.png
		typedef enum 
		{
			/// @brief 
			Application = 'A',
			Error = 'E',
			Warning = 'W',
			Ok = 'O',
			Network = 'N',
			Info = 'I',
			Folder = 'F',
			Component = 'C',
			Mail = 'M',
			Download = 'D',
			Sound = 'S'
		} notifyIcon;

		typedef enum
		{
			/// @brief не закрывать автоматически
			NoAutoClose = 'd',
			
			/// @brief не закрываеть по клику
			NoClose = 'c',

			/// @brief Есть заголовок
			Title = 't',

			ProgressBar = 'p'
		} notifyKey;

		/// @brief Уведмление
		/// @param Title Заголовок, может быть пустым если заголовок не нужен
		/// @param Text текст после заголовка
		/// @param icon иконка
		/// @param keys ключи
		void Notify(const std::string &Title, const std::string &Text, notifyIcon icon = notifyIcon::Info, const notifyKey (&keys)[4] = {notifyKey::Title, (notifyKey)0, (notifyKey)0, (notifyKey)0});
		

		/// @brief Уведомление об ошибке через увдомления системы
		/// @param Title Заголовок уведомления об ошибке
		/// @param Text текст
		inline void ErrorNotify(const std::string &Title, const std::string &Text)
		{
			std::string a = "\"'" + Title + "\n" + Text + "' -E -t";
			_ksys_exec("/sys/@notify", (char*)a.c_str(), false);
		}


		/// @brief Версия ядра
		struct CoreVersion
		{
			union
			{
				/// @brief Версия
				uint32_t version;
				struct
				{
					uint8_t a;
					uint8_t b;
					uint8_t c;
					uint8_t d;
				};
			};

			/// @brief Зарезервированно
			uint8_t reserved;

			/// @brief Ревизия
			uint16_t Rev;
		};

		/// @brief Получить версию ядра
		/// @return Указатель на структуру версии ядра
		inline CoreVersion* GetCoreVersion()
		{
			CoreVersion* p = new CoreVersion;
			asm_inline(
				"int $0x40"
				:"=a"(p)
				:"a"(18), "b"(13)
			);
			return p;
		}

		/// @brief Получить тактовую частоту процессора
		/// @return тактовая частота (по модулю 2^32 тактов = 4ГГц)
		inline uint32_t GetCPUClock()
		{
			return _ksys_get_cpu_clock();
		}

	} // namespace OS

} // namespace KolibriLib


#endif // __OS_H__