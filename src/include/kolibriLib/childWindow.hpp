#pragma once

#ifndef __CHILDWINDOW_H__
#define __CHILDWINDOW_H__


#include <string.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include <string>

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

        void RenderMessageWindow(void*);

        /// \brief Создать окно с сообщением
        /// \param Message сообщение
        /// \param Title Заголовок
        void MessageBox(const std::string& _Message, const std::string& _Title);

        /// \brief окошко с ошибкой
        /// \param ErrorMessage сообщение об ощибке
        inline void ErrorWindow(const std::string& ErrorMessage);
    }
}

#endif // __CHILDWINDOW_H__