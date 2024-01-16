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
#include "image.hpp"

namespace KolibriLib
{
    /// @brief Дочерние окна
    namespace childWindow
    {
        // Я вам запрещаю записывать значения в эту переменную
        std::string Message, Title;
        // Я вам запрещаю записывать значения в эту переменную
        bool Used = false;
        /// @brief Тип
        short type;
        /// @brief Картинка, ставится в левой части окна
        UI::Image::img img;

        //Функция потока нового окна
        void RenderMessageWindow(void)
        {
            std::string _Message    = Message;
            std::string _Title      = Title;
            
            const point<unsigned> MinWindowSize   = {256, 128};
            const point<unsigned> ButtonSize      = {64, 48};

            window::Window window(_Title, MinWindowSize);

            {
                unsigned lenght = _Message.length() * 9;

                if (lenght > MinWindowSize.x)               //Окно растягивается если текст длинный
                {
                    window.SetSize({lenght, MinWindowSize.y});
                }
            }

            window.Render();

            point<unsigned> WindowSize = window.GetSize();

            window.CreateText({0,0}, window.GetSize(), _Message);
            unsigned button = window.CreateButton({window.GetWindowSize().x - WindowSize.x - ButtonSize.x, ButtonSize.y + WindowSize.y }, ButtonSize, "Ok");

            while (true)
            {
                unsigned Event = window.Handler(); // Ждём пока не появится какой либо ивент

                if(Event == KSYS_EVENT_BUTTON)
                {
                    if(button == window.GetPressedButton())
                    {
                        window.~Window();
                    }
                }

                if(window._Exit)
                {
                    window.~Window();
                }
            }
        }

        

        /// \brief Создать окно с сообщением
        /// \param Message сообщение
        /// \param Title Заголовок
        void MessageBox(const std::string& _Message, const std::string& _Title)
        {
            while (true)
            {
                if (!Used) // Проверка на то создают ли другие потоки ещё MessageWindow.
                {          // Это так потому что глобальная переменная Newindex одна на всех
                    Used = true;

                    Message = _Message;
                    Title = _Title;
                    Used = true;

                    Thread::CreateThread((void(*))RenderMessageWindow, 4096);

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
        inline void ErrorWindow(const std::string& ErrorMessage)
        {
            MessageBox(ErrorMessage, "Error!");
        }
    }
}

#endif // __CHILDWINDOW_H__