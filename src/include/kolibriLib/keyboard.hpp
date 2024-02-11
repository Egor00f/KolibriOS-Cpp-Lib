#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <sys/ksys.h>

namespace KolibriLib
{
    namespace keyboard
    {
        /// @brief Проверить какая клавиша клавиатуры нажата
        /// @return код(char) нажатой клавишы клавиатуры
        char CheckKeyboard();

        enum ControlKeys
        {
            LeftShift	= KSYS_CONTROL_LSHIFT,  //Хоспади автор ksys.h зачем такие страшные и длинные шифры, нипанятна же ничего
            RightShift	= KSYS_CONTROL_RSHIFT,
            LeftCtrl	= KSYS_CONTROL_LCTRL,
            RightCtrl	= KSYS_CONTROL_RCTRL,
            LeftAlt		= KSYS_CONTROL_LALT,
            RightAlt	= KSYS_CONTROL_RALT,
            CapsLock	= KSYS_CONTROL_CAPS,
            NumLock 	= KSYS_CONTROL_NUM_LOCK,
            ScrollLock	= KSYS_CONTROL_SCROLL_LOCK
        };

        /// @brief Получить состояние управляющих клавиш
        /// @return Возвращает имя конгстрольной клавиши из списка @link ControlKeys
        unsigned GetControlKey();


        /// @brief Установить "горячую клавишу"
		/// @param controlkeys клавиши
		/// @return true если успешно, иначе false
        /// @warning not done!
		bool InstallHotKey(uint16_t controlkeys);

        /// @brief Удалить "горячую клавишу"
        /// @return true если успешно, иначе false
        /// @warning not done!
        bool DeleteHotKey();

        
    } // namespace keyboard
} // namespace KolibriLib


#endif // __KEYBOARD_H__