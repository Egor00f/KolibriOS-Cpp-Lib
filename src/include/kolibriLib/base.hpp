#pragma once

#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>

#include <string.h>
#include <stdlib.h>
#include <string>
#include "filesystem.hpp"


/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{
    const int AAANUMBER = 65536;

    /// \brief Просто точка
    struct point
    {
        unsigned x;
        unsigned y;
    };

    /// @brief Путь по которому сохраняются настройки приложений
    const std::string ConfigFolder = "/sys/etc";

    

    /// @brief Работа с системой
    namespace OS
    {

        /// \brief Таблица стандартных(системных) цветов
        ksys_colors_table_t sys_color_table;

        ksys_colors_table_t GetSystemColors()
        {
            _ksys_get_system_colors(&sys_color_table);
            return sys_color_table;
        }

        /// \brief Ждать ивента
        /// \return Ивент
        inline unsigned int WaitEvent()
        {
            return _ksys_wait_event();
        }

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
            if(filesystem::Exist(AppName))//Проверка на существование
            {
                char *a = "";
                strcat(a, args.c_str());
                return _ksys_exec(AppName.c_str(), a);
            }
            else
            {
                return -1;
            }
        }

        inline ksys_time_t GetTime()
        {
            return _ksys_get_time();
        }

        /* inline char GetKey()
        {
            uint32_t val;
            asm_inline(
                "int $0x40"
                : "=a"(val)
                : "a"(2)
            );

            return;
        } */

    }

    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(unsigned time)
    {
        _ksys_delay(time);
    }

    /// @brief инициализация
    void init()
    {
        _ksys_set_event_mask(0x07);
        OS::GetSystemColors();
    }
}



#endif // __BASE_H__