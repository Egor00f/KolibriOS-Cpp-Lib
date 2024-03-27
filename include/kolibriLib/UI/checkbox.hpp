#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include <sys/ksys.h>

#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/button.hpp>
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
        private:
            int _style;
            bool _status;

        public:
            /// @brief Стиль Чекбокса
            enum style
            {
                /// @brief По вид умолчанию, квадрат
                Default,
                /// @brief В виде круга
                Circle,
                /// @brief Квадрат с со сглаженными углами
                /// @warning Не реализованно (пока что)
                Smoth,
            };

            CheckBox(const Coord& coord = {0, 0}, const Size& size = {32, 16}, const int& style = 0, const Colors::Color& CheckBoxBorderColor = OS::GetSystemColors().work_text, const Colors::Color& BackgroundColor = OS::GetSystemColors().work_area, const unsigned& Margin = DefaultMargin);

            /// @brief Отрисовать Checkbox
            void Render();

            /// @brief Обработчик кнопки
            bool Handler();
        };
    } // namespace UI
    
} // namespace KolibriLib


#endif // __CHECKBOX_H__