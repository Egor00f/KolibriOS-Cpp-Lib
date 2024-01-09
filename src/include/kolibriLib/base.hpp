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
    /// @brief Сообщение всем функциям что нужно завершать работу
    bool EXIT = false;
    /// @brief Код ошибки
    /// @paragraph int main(){/*...*/ return EXITCODE; }
    int EXITCODE = 0;

    /// \brief Просто точка
    struct point
    {
        unsigned x;
        unsigned y;
    };
  
    /// @brief Работа с системой
    namespace OS
    {

        /// \brief Таблица стандартных(системных) цветов
        ksys_colors_table_t sys_color_table;

        /// @brief Получить системные цвета
        /// @paragraph Функция изменяет переменную @link sys_color_table
        /// @return Таблица системных цветов
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

        /// @brief Получить системное время
        /// @return 
        inline ksys_time_t GetTime()
        {
            return _ksys_get_time();
        }


    }

    /// \brief Подождать
    /// \param time время задержки(в 1/100 секунды)
    inline void Wait(unsigned time)
    {
        _ksys_delay(time);
    }

    /// @brief Инициализация
    /// @paragraph Просто не заморачиваяся, и вызывай в начале программы
    void init()
    {
        _ksys_set_event_mask(0x07);
        OS::GetSystemColors();
    }

    /// @brief Проверить какая клавиша клавиатуры нажата
    /// @return код(char) нажатой клавишы клавиатуры
    char CheckKeyboard()
    {
        return _ksys_get_key().code;
    }
}



#endif // __BASE_H__