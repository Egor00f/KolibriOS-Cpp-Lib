#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__

/*
    Тут тип базовый функционал работы с окном
*/

#include <sys/ksys.h>
#include "types.hpp"
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

        /// @brief Свернуть окно
        inline void MinimizeWindow();

        /// @brief Свернуть все окна
        inline void MinimizeAllWindows();

        /// @brief Список констант положения окна относительно других окон:
        enum Pos{
            BackGround = -2,
            AlwaysBack = -1,
            Normal = 0,
            AlwaysTop = 1
        };

        /// @brief Получить положение окна относительно других окон
        /// @return одна из констант из списка @link Pos
        inline int GetWindowPos();

        /// @brief Изменить положение окна относительно дроугих окон
        /// @param pos 
        /// @param pid процесс
        /// @return false если ошибка
        inline bool SetWindowPos(int pos, Thread::PID pid = -1);

        /// @brief Получить высоту скина(заголовка окна)
        /// @return высота скина
        inline unsigned GetSkinHeight();

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__