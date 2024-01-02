#pragma once

#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__

extern "C"{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/ksys.h>
}
#include <string>

#include "base.hpp"

namespace KolibriLib
{

    namespace childWindow
    {

        const std::string MessageBoxName("messagebox");

        /// @brief Создать окно с сообщением
        /// @param Message сообщение
        /// @param Title Заголовок
        void MessageBox(std::string Message, std::string Title)
        {
            std::string A("/");
            std::string B(" ");
            OS::Exec(BinPath + A + MessageBoxName, Title + B + Message);
        }

        /// @brief Создать окно с сообщением
        /// @param Message сообщение
        /// @param Title Заголовок
        void MessageBox(const char *Message, const char *Title)
        {
            char *ARGS = "";

            strcat(ARGS, Title);
            strcat(ARGS, " ");
            strcat(ARGS, Message);

            char *A = "";

            strcat(A, BinPath.c_str());
            strcat(A, MessageBoxName.c_str());

            OS::Exec(A, ARGS);
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