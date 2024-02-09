#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include <sys/ksys.h>

#include <string>

#include "small.hpp"
#include "UI.hpp"
#include "button.hpp"
#include "graphic.hpp"
#include "color.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Класс для работы с чекбоксами
        /// @paragraph Это просто чекбокс, ему можно задать различные стили
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

            CheckBox(const Coord& coord = {0, 0}, const Size& size = {32, 16}, const int& style = 0, const Colors::Color& CheckBoxBorderColor = OS::sys_color_table.work_text, const Colors::Color& BackgroundColor = OS::sys_color_table.work_area, const unsigned& Margin = DefaultMargin);
            ~CheckBox();

            /// @brief Отрисовать Checkbox
            void Render();

            /// @brief Обработчик кнопки
            bool Handler();
        };
    } // namespace UI
    
} // namespace KolibriLib


#endif // __CHECKBOX_H__