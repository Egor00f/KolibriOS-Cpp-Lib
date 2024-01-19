#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__


namespace keyboard
{
    /// @brief Проверить какая клавиша клавиатуры нажата
    /// @return код(char) нажатой клавишы клавиатуры
    char CheckKeyboard()
    {
        return _ksys_get_key().code;
    }

} // namespace keyboard

#endif // __KEYBOARD_H__