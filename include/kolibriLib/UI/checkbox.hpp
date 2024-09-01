#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include <sys/ksys.h>

#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/buttons/button.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/color.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Класс для работы с чекбоксами
        /// @note Это просто чекбокс, ему можно задать различные стили
        class CheckBox : public buttons::Button
        {
        public:

            /// @brief Стиль Чекбокса
            typedef enum
            {
                /// @brief По вид умолчанию, квадрат
                Default,

                /// @brief В виде круга
                Circle,

                /// @brief Квадрат с со сглаженными углами
                /// @warning Не реализованно (пока что)
                Smoth
            } style;

            CheckBox(const UDim &coord = point(0), const UDim &size = DefaultSize, const style &Style = style::Default, const Colors::Color &CheckBoxBorderColor = Globals::SystemColors.work_text, const Colors::Color &BackgroundColor = Globals::SystemColors.work_area, const unsigned &Margin = DefaultMargin);

            /// @brief Отрисовать рамки
            void DrawBorder() const;

            /// @brief Отрисовать Checkbox
            void Render() const;

            /// @brief Изменить стиль
            /// @param s 
            void SetStyle(style s);

            bool GetChecked() const;

            void OnButtonEvent(buttons::ButtonID PressedButtonID);

        private:
            Colors::Color _BorderColor;
            style _style;
            bool checked;
        };
    } // namespace UI
    
} // namespace KolibriLib


#endif // __CHECKBOX_H__