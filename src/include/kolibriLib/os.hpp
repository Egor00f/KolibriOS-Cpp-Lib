#ifndef __OS_H__
#define __OS_H__

#include <string>

#include <sys/ksys.h>
#include <string.h>
#include <stdlib.h>

#include "small.hpp"
#include "filesystem.hpp"

namespace KolibriLib
{
    /// @brief Работа с системой
    namespace OS
    {

        /// \brief Таблица стандартных(системных) цветов
        ksys_colors_table_t sys_color_table;

        /// @brief Получить системные цвета
        /// @paragraph Функция изменяет переменную @link sys_color_table
        /// @return Таблица системных цветов
        ksys_colors_table_t GetSystemColors();

        /// \brief Ждать ивента
        /// \return Ивент
        inline unsigned int WaitEvent();

        /// \brief Ждать ивента
        /// \param Таймаут (в 1/100 секунды)
        /// \return Ивент
        inline unsigned int WaitEvent(uint32_t TimeOut)
        {
            _ksys_wait_event_timeout(TimeOut);
        }

        /// \brief Проверить пришёл ли ли ивент
        /// \return Ивен
        inline unsigned int CheckEvent()
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
} // namespace KolibriLib


#endif // __OS_H__