#pragma once

#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include <string>
#include <vector>
#include <thread>

#include "base.hpp"
#include "window.hpp"
#include "thread.hpp"

namespace KolibriLib
{
    /// @brief Дочерние окна
    namespace childWindow
    {
        // Я вам запрещаю записывать значения в эту переменную
        std::string Message, Title;
        // Я вам запрещаю записывать значения в эту переменную
        bool Used = false;

        //Функция потока нового окна
        void RenderMessageWindow(void)
        {
            std::string _Message    = Message;
            std::string _Title      = Title;
            
            window::Window window(_Title, {256,128});

            point WindowSize = window.GetSize();

            window.CreateText({window.GetMargin(), WindowSize.y / 2 }, {WindowSize.x, WindowSize.y / 2}, _Message);

            while (true)
            {
                unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент
                switch (Event)
                {
                case KSYS_EVENT_REDRAW:
                    window.Render();
                    break;
                case KSYS_EVENT_BUTTON:
                    unsigned button = UI::buttons::GetPressedButton();
                    switch (button)
                    {
                    case 1:                                 //Если нажата кнопка X(та что закрывает окно)
                        return;
                    }
                }
            }
        }

        

        /// \brief Создать окно с сообщением
        /// \param Message сообщение
        /// \param Title Заголовок
        void MessageBox(std::string _Message, std::string _Title)
        {
            while (true)
            {
                if (!Used) // Проверка на то создают ли другие потоки ещё MessageWindow.
                {          // Это так потому что глобальная переменная Newindex одна на всех
                    Used = true;

                    Message = _Message;
                    Title = _Title;
                    Used = true;

                    
                    Thread::CreateThread((void(*))RenderMessageWindow, 2048);

                    Used = false; // Я всё, заКОНЧИЛ. Свободно!
                    return;
                }
                else // если занято то ждём
                {
                    Wait(1);
                }
            }
        }

        /// \brief окошко с ошибкой
        /// \param ErrorMessage сообщение об ощибке
        inline void ErrorWindow(std::string ErrorMessage)
        {
            MessageBox(ErrorMessage, "Error!");
        }
    }
}

#endif // __CHILDWINDOW_H__