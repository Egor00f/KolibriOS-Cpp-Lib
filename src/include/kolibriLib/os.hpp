#ifndef __OS_H__
#define __OS_H__

#include "small.hpp"
#include "filesystem.hpp"
#include "color.hpp"

namespace KolibriLib
{
    /// @brief Работа с системой
    namespace OS
    {

        /// \brief Таблица стандартных(системных) цветов
        Color::ColorsTable sys_color_table;

        /// @brief Получить системные цвета
        /// @paragraph Функция изменяет переменную @link sys_color_table
        /// @return Таблица системных цветов
        Color::ColorsTable GetSystemColors()
        {
            _ksys_get_system_colors(&sys_color_table);
            return sys_color_table;
        }

        /// @brief Ивент
        typedef unsigned int Event;

        enum Events
        {
            None    = KSYS_EVENT_NONE,
            Redraw  = KSYS_EVENT_REDRAW,
            Button  = KSYS_EVENT_BUTTON,
            Mouse   = KSYS_EVENT_MOUSE,
            Key     = KSYS_EVENT_KEY,
            Desktop = KSYS_EVENT_DESKTOP,
            Debug   = KSYS_EVENT_DEBUG,
            Exit    = 200
        };

        /// \brief Ждать ивента
        /// \return Ивент
        inline Event WaitEvent()
        {
            return _ksys_wait_event();
        }

        /// \brief Ждать ивента
        /// \param Таймаут (в 1/100 секунды)
        /// \return Ивент
        inline Event WaitEvent(uint32_t TimeOut)
        {
            _ksys_wait_event_timeout(TimeOut);
        }

        /// \brief Проверить пришёл ли ли ивент
        /// \return Ивен
        inline Event CheckEvent()
        {
            return _ksys_check_event();
        }

        /// \brief Запустить программу
        /// \param AppName путь до программы + имя
        /// \param args аргументы
        /// \return то что возвращает сама программа, -1 если исполняемы файл не найден
        inline int Exec(std::string AppName, std::string args)
        {
            if (filesystem::Exist(AppName)) // Проверка на существование
            {
                char *a;
                strcat(a, args.c_str());
                return _ksys_exec(AppName.c_str(), a);
            }
            else
            {
                return -1;
            }
        }

        /// @brief Получить системное время
        /// @return
        inline ksys_time_t GetTime()
        {
            return _ksys_get_time();
        }

        

    } // namespace OS

    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(unsigned int time)
    {
        _ksys_delay(time);
    }

} // namespace KolibriLib


#endif // __OS_H__