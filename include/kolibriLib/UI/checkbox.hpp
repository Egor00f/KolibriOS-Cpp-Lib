#ifndef __CHECKBOX_HPP__
#define __CHECKBOX_HPP__

#include <include_ksys.h>

#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/buttons/button.hpp>
#include <kolibriLib/color.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Класс для работы с чекбоксами
        /// @paragraph Это просто чекбокс, ему можно задать различные стили
        /// @example checkboxExample.cpp
        class CheckBox : public buttons::Button
        {
        public:

            /// @brief Стиль Чекбокса
            enum class style
            {
                /// @brief По вид умолчанию, квадрат
                Default,

                /// @brief В виде круга
                Circle,

                /// @brief Квадрат с со сглаженными углами
                /// @warning Не реализованно (пока что)
                Smoth
            };

            CheckBox() = default;

            /// @brief Конструктор
            /// @param coord координаты вехнего левого угла
            /// @param size рамеры
            /// @param Style стиль
            /// @param CheckBoxBorderColor 
            /// @param BackgroundColor 
            /// @param Margin 
            CheckBox(const UDim &coord = point(0), const UDim &size = DefaultSize, const style &Style = style::Default, const Colors::Color &CheckBoxBorderColor = Globals::SystemColors.work_text, const Colors::Color &BackgroundColor = Globals::SystemColors.work_area, const unsigned &Margin = DefaultMargin);

            /// @brief 
            /// @param a 
            CheckBox(const CheckBox& a);

            /// @brief Отрисовать рамки
            void DrawBorder() const;

            /// @brief Отрисовать Checkbox
            void Render() const override;

            /// @brief Изменить стиль
            /// @param s Новый стиль
            void SetStyle(style s);

            /// @brief Получить состояние чекбокса
            /// @return 
            bool GetChecked() const;

            void OnButtonEvent(buttons::ButtonID PressedButtonID);

            void SetBorderColor(const Colors::Color& NewBorderColor);
            Colors::Color GetBorderColor() const;

            void swap(CheckBox& a);

            CheckBox& operator = (const CheckBox&) = default;

            bool operator == (const CheckBox&) const;
            bool operator != (const CheckBox&) const;
        private:
            Colors::Color _BorderColor;
            style _style = style::Default;
            mutable bool checked;
        };
    } // namespace UI
    
} // namespace KolibriLib


#endif // __CHECKBOX_HPP__