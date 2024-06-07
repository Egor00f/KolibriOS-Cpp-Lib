#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__


#include <string.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/window/window.hpp>
#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/system/os.hpp>

namespace KolibriLib
{
    /// @brief Дочерние окна
    namespace childWindow
    {
        // Я вам запрещаю записывать значения в эту переменную
        std::string Message, Title;
        // Я вам запрещаю записывать значения в эту переменную
        bool Used = false;

        //Функция потока окна с сообщением
        void RenderMessageWindow(void*);

        /// \brief Создать окно с сообщением
        /// \param Message сообщение
        /// \param Title Заголовок
        void MessageBox(const std::string &_message, const std::string &_title)
        {
            while (true)
            {
                if (!Used) // Проверка на то создают ли другие потоки ещё MessageWindow.
                {          // Это так потому что глобальная переменная Newindex одна на всех
                    Used = true;

                    Message = _message;
                    Title = _title;

                    Thread::CreateThread(RenderMessageWindow, 8192); // Выделил памяти чуть больше, чтоб точно хватило

                    Used = false; // Я всё, заКОНЧИЛ. Свободно!
                    break;
                }
                else // если занято то ждём
                {
                    _ksys_thread_yield();
                }
            }
        }

        /// \brief окошко с ошибкой
        /// \param ErrorMessage сообщение об ощибке
        inline void ErrorWindow(const std::string &ErrorMessage)
        {
            MessageBox(ErrorMessage, "Error!");
        }

        void RenderMessageWindow(void *)
        {
            std::string _Message = Message;
            std::string _Title = Title;

            window::Window window(_Title);

            Size WindowSize = window.GetSize();

            window.AddElement(UI::text::TextLabel(UI::UDim(0, UI::DefaultMargin, 0, UI::DefaultMargin), UI::UDim(1, 0, 0.5, 0), _Message, 16));

            const unsigned ButtonSize = 40;

            UI::buttons::Button OK(UDim(0.72, 0, 0.7, 0), UDim(0.2, 0, 0.2, 0));
            OK.Add("OK");

            window::Window::ElementNumber ok = window.AddElement(OK);

            OK.~Button();

            window.Render();
            while (true)
            {
                OS::Event event = window.Handler();
                if (event == OS::Events::Exit)
                {
                    window.~Window();
                    _ksys_exit();
                }
            }
        }
    }
}

#endif // __CHILDWINDOW_H__