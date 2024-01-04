#pragma once

#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include <string>
#include <thread>

#include "base.hpp"
#include "window.hpp"

namespace KolibriLib
{

    namespace childWindow
    {

        void MessageWindow(std::string Message, std::string Title)
        {
            window::initWindow();

            window::DrawWindow({100, 100}, {256, 128}, Title);
            UI::text::DrawText(Message, {window::MARGIN, (128 / 2) - UI::text::GetTextSize()});


            while (true)
            {
                unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент
                switch (Event)
                {
                case KSYS_EVENT_REDRAW:
                    point mouse = mouse::GetMousePositionInWindow();
                    window::StartRedraw();
                    window::DrawWindow(mouse, window::DefaultWindowSize, Title);
                    UI::text::DrawText(Message, {window::MARGIN, (128 / 2) - UI::text::GetTextSize()});
                    window::EndRedraw();
                    break;
                case KSYS_EVENT_BUTTON:
                    if (UI::buttons::GetPressedButton() == 1) // Если нажат крестик
                    {
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        /// @brief Создать окно с сообщением
        /// @param Message сообщение
        /// @param Title Заголовок
        void MessageBox(std::string Message, std::string Title)
        {
            void *th_stack = malloc(1024);
            if (!th_stack)
            {
                _ksys_debug_puts("Memory allocation error for thread!");
                return;
            }
            _ksys_create_thread(MessageWindow, th_stack + 1024);
        }

        /// @brief Создать окно с сообщением
        /// @param Message сообщение
        /// @param Title Заголовок
        void MessageBox(const char *Message, const char *Title)
        {
            void *th_stack = malloc(1024);
            if (!th_stack)
            {
                _ksys_debug_puts("Memory allocation error for thread!");
                return;
            }
            _ksys_create_thread(MessageWindow, th_stack + 1024);
        }

        /// @brief окошко с ошибкой
        /// @param ErrorMessage сообщение об ощибке
        inline void ErrorWindow(std::string ErrorMessage)
        {
            MessageBox(ErrorMessage, "Error!");
        }

        /// @brief окошко с ошибкой
        /// @param ErrorMessage сообщение об ощибке
        inline void ErrorWindow(const char *ErrorMessage)
        {
            MessageBox(ErrorMessage, "Error!");
        }
    }
}

#endif // __CHILDWINDOW_H__