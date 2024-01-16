#ifndef __WINDOWBASE_H__
#define __WINDOWBASE_H__


#include <sys/ksys.h>


namespace KolibriLib
{
    

    /// @brief Работа с окном
    namespace window
    {


        /// @brief Размер окна поумолчанию
        const point<unsigned> DefaultWindowSize = {400, 400};

        /// @brief Соординаты окна по умолчанию
        const point<unsigned> DefaultWindowCoord = {100, 100};



        /// @brief Снять фокус с окна
        /// @param slot слот окна
        inline void UnfocusWindow(int slot)
        {
            _ksys_unfocus_window(slot);
        }
        /// @brief Поставить фокус на окно
        /// @param slot слот окна
        inline void FocusWindow(int slot)
        {
            _ksys_focus_window(slot);
        }

    } // namespace window
    

} // namespace KolibriLib


#endif // __WINDOWBASE_H__