#pragma once

#ifndef __BASE_H__
#define __BASE_H__



extern "C"
{
    #include <sys/ksys.h>
    #include <string.h>
    #include <stdlib.h>
}
#include <string>


namespace KolibriLib
{
    const int AAANUMBER = 65536;

    /// @brief Просто точка
    struct point
    {
        unsigned x;
        unsigned y;
    };

    // Папка где лежат программы
    const std::string BinPath("/sys/bin");

    namespace OS
    {

        /// @brief Таблица стандартных(системных) цветов
        ksys_colors_table_t sys_color_table;

        void GetSystemColors()
        {
            _ksys_get_system_colors(&sys_color_table);
        }

        /// @brief Ждать ивента
        /// @return uint32_t
        inline uint32_t WaitEvent()
        {
            return _ksys_wait_event();
        }

        inline uint32_t WaitEvent(uint32_t TimeOut)
        {
            _ksys_wait_event_timeout(TimeOut);
        }

        /// @brief Проверить есть ли ивент
        /// @return uint32_t
        inline uint32_t CheckEvent()
        {
            return _ksys_check_event();
        }

        /// @brief Запустить программу
        /// @param AppName путь до программы + имя
        /// @param args аргументы
        /// @return то что возвращает сама программа
        inline int Exec(std::string AppName, std::string args)
        {
            char *a = "";
            strcat(a, args.c_str());
            return _ksys_exec(AppName.c_str(), a);
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

    /// @brief Подождать
    /// @param time время задержки
    inline void Wait(unsigned time)
    {
        _ksys_delay(time);
    }
    
    
}



#endif // __BASE_H__