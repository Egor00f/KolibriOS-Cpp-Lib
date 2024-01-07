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

        struct MessageWindowData
        {
            std::string Message, Title;
            bool use = false;           //Знак того используется ли этот элемент массива
        };

        // Я вам запрещаю записывать значения в эту переменную
        unsigned Newindex = 0;
        // Я вам запрещаю записывать значения в эту переменную
        bool Used = false;

        std::vector<MessageWindowData> MessageWindowDataList;

        unsigned GetMessageWindowDataListId(MessageWindowData data)
        {
            for(unsigned i = 0; i < MessageWindowDataList.size(); i++)  //Проходим по всему массиву
            {                                                           //Если встречается свободный элемент,
                if(!MessageWindowDataList[i].use)                       //То используем его
                {                                                       //Иначе создаём новый и использем тоже новый
                    MessageWindowDataList[i] = data;
                    return i;
                }
            }
            MessageWindowDataList.push_back(data);
            return MessageWindowDataList.size();
        }


        void FreeMessageWindowDataListId(unsigned id)
        {
            MessageWindowDataList[id].use = false;  //Этот элемент теперь не используется
        }

        //Функция потока нового окна
        int RenderMessageWindow()
        {
            unsigned index = Newindex;
            window::initWindow();

            window::DrawWindow({100, 100}, {256, 128}, MessageWindowDataList[index].Title);
            UI::text::DrawText(MessageWindowDataList[index].Message, {window::MARGIN, (128 / 2) - UI::text::GetTextSize()});

            while (true)
            {
                unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент
                switch (Event)
                {
                case KSYS_EVENT_REDRAW:
                    point mouse = mouse::GetMousePositionInWindow();
                    window::StartRedraw();
                    window::DrawWindow(mouse, window::DefaultWindowSize, MessageWindowDataList[index].Title);
                    UI::text::DrawText(MessageWindowDataList[index].Title, {window::MARGIN, (128 / 2) - UI::text::GetTextSize()});
                    window::EndRedraw();
                    break;
                case KSYS_EVENT_BUTTON:
                    switch (UI::buttons::GetPressedButton())
                    {
                    case 1:                                 //Если нажата кнопка X(та что закрывает окно)
                        FreeMessageWindowDataListId(index);
                        _ksys_exit();                       //Остановка потока
                        break;
                    
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
            return 0;
        }



        /// @brief Окно с сообщением
        class MessageWindow
        {
        private:
            unsigned _id;
        public:
            /// @brief Кониструктор
            /// @param Message Сообщение
            /// @param Title Заголовок
            MessageWindow(std::string Message, std::string Title);

            ~MessageWindow();
            void Render(std::string Message, std::string Title);

            /// @brief Изменить сообщение
            /// @param Text новое сообщение
            void SetMessage(std::string Text);

            /// @brief Изменить заголовок окна
            /// @param Text новый заголовок
            void SetTitle(std::string Text);
        };

        MessageWindow::MessageWindow(std::string Message, std::string Title)
        {
            Render(Message, Title);
        }
        
        MessageWindow::~MessageWindow()
        {
        }
        //Не вызывать! я хз чё будет происходить.
        void MessageWindow::Render(std::string Message, std::string Title)
        {
            while (true)
            {
                if (!Used)          //Проверка на то создают ли другие потоки ещё MessageWindow.
                {                   //Это так потому что глобальная переменная Newindex одна на всех
                    Used = true;

                    _id =  GetMessageWindowDataListId((MessageWindowData){Message, Title, true});

                    Newindex = _id;

                    Thread::CreateThread(RenderMessageWindow);

                    Used = false;   //Я всё, заКОНЧИЛ. Свободно!
                }
                else        //если занято то ждём
                {
                    Wait(1);
                }
                
            }
            
        }

        void KolibriLib::childWindow::MessageWindow::SetMessage(std::string Text)
        {
            MessageWindowDataList[_id].Message = Text;
        }

        void KolibriLib::childWindow::MessageWindow::SetTitle(std::string Text)
        {
            MessageWindowDataList[_id].Title = Text;
        }

        /// \brief Создать окно с сообщением
        /// \param Message сообщение
        /// \param Title Заголовок
        unsigned MessageBox(std::string Message, std::string Title)
        {
            while (true)
            {
                if (!Used) // Проверка на то создают ли другие потоки ещё MessageWindow.
                {          // Это так потому что глобальная переменная Newindex одна на всех
                    Used = true;

                    unsigned _id = GetMessageWindowDataListId((MessageWindowData){Message, Title, true});

                    Newindex = _id;

                    Thread::CreateThread(RenderMessageWindow);

                    Used = false; // Я всё, заКОНЧИЛ. Свободно!
                    return _id;
                }
                else // если занято то ждём
                {
                    Wait(1);
                }
            }
            return 0;
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