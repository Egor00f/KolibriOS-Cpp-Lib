#pragma once

#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__


#include <string.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include <string>
#include <vector>

#include "small.hpp"
#include "UI.hpp"
#include "window.hpp"
#include "thread.hpp"
#include "os.hpp"


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
        void RenderMessageWindow()
        {
            std::string _Message    = Message;
            std::string _Title      = Title;
            
            window::Window window(_Title, {256,128});

            UI::Size WindowSize = window.GetSize();

            window.CreateText(UI::text::TextLabel({(int)window.GetMargin(), (int)window.GetMargin()}, {WindowSize.x, WindowSize.y / 2}, _Message));

            const unsigned ButtonSize = 40;

            UI::buttons::Button OK({(int)WindowSize.x - (int)window.GetMargin(), WindowSize.y / 2}, {ButtonSize, WindowSize.y / 2}, 0);
            OK.SetText("Ok");

            unsigned ok = window.CreateButton(OK);

            OK.~Button();

            

            window.Render();
            while (true)
            {
                OS::Event event = window.Handler();
                if(event = OS::Events::Exit)
                {
                    window.~Window();
                    return;
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

                    Thread::CreateThread((void(*)(void*))RenderMessageWindow, 4096);

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