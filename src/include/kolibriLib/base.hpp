#pragma once

#ifndef __BASE_H__
#define __BASE_H__

#include <sys/ksys.h>
#include <string.h>
#include <stdlib.h>
#include <kolibri_libimg.h>


#include <string>
#include <fstream>

#include "small.hpp"
#include "filesystem.hpp"
#include "mouse.hpp"
#include "os.hpp"

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{
     
    

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
        if(kolibri_libimg_init() == -1)
        {
            childWindow::ErrorWindow("Can't loaded libimg!");
            exit(0);
        }
        _ksys_set_event_mask(0x07); //Просто надо
        OS::GetSystemColors();      //Получение системмных цветов
        /*
        if(filesystem::Exist("/kolibrios/etc"))
        {
            filesystem::mkdir("/kolibrios/etc");
        }
        
        char *a;
        strcat(a, ConfigurationDir.c_str());
        strcat(a, "cursors");
        std::ofstream file(a);

        if(file.is_open())
        {
            std::string buff;
            file << buff;
            if(buff == "cursors loaded!")
            {

            }
            else
            {
                mouse::Cursor.pointer   = mouse::LoadCursor(CursorsDir + "pointer.cur");
                mouse::Cursor.dgn1      = mouse::LoadCursor(CursorsDir + "dgn1.cur");
                mouse::Cursor.dgn2      = mouse::LoadCursor(CursorsDir + "dgn2.cur");
                mouse::Cursor.link      = mouse::LoadCursor(CursorsDir + "link.cur");
                mouse::Cursor.horz      = mouse::LoadCursor(CursorsDir + "horz.cur");
                mouse::Cursor.vert      = mouse::LoadCursor(CursorsDir + "vert.cur");
                mouse::Cursor.beam      = mouse::LoadCursor(CursorsDir + "beam.cur");
                mouse::Cursor.busy      = mouse::LoadCursor(CursorsDir + "busy.cur");
            }
        }
        else
        {
            
        }
        file.close();*/
    }

    /// @brief Проверить какая клавиша клавиатуры нажата
    /// @return код(char) нажатой клавишы клавиатуры
    char CheckKeyboard()
    {
        return _ksys_get_key().code;
    }
}

ksys_colors_table_t KolibriLib::OS::GetSystemColors()
{
    _ksys_get_system_colors(&sys_color_table);
    return sys_color_table;
}

unsigned int KolibriLib::OS::WaitEvent()
{
    return _ksys_wait_event();
}

#endif // __BASE_H__