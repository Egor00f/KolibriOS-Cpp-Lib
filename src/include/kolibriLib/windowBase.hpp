#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__

/*
    Тут тип базовый функционал работы с окном
*/

#include <sys/ksys.h>
#include "UI.hpp"
#include "thread.hpp"

namespace KolibriLib
{

    /// @brief Работа с окном
    namespace window
    {
        
        /// @brief Размер окна поумолчанию
        const UI::Size DefaultWindowSize = {400, 400};

        /// @brief Соординаты окна по умолчанию
        const UI::Coord DefaultWindowCoord = {100, 100};



        

        /// @brief Снять фокус с окна
        /// @param slot слот окна
        inline void UnfocusWindow(Thread::Slot slot);

        /// @brief Поставить фокус на окно
        /// @param slot слот окна
        inline void FocusWindow(Thread::Slot slot);

        /// @brief Получить слот активного окна
        /// @return 
        Thread::Slot GetActiveWindow();

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__