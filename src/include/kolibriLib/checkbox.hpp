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

            CheckBox(Coord coord = {0, 0}, Size size = {32, 16}, int style = 0, Color::Color CheckBoxBorderColor = OS::sys_color_table.work_text, Color::Color BackgroundColor = OS::sys_color_table.work_area, unsigned Margin = DefaultMargin);
            ~CheckBox();

            void Render();

            /// @brief Обработчик кнопки
            bool Handler();
        };

        CheckBox::CheckBox(Coord coord, Size size, int style, Color::Color CheckBoxBorderColor, Color::Color BackgroundColor, unsigned Margin) : Button(coord, size, CheckBoxBorderColor, Margin)
        {
            _style = style;
        }

        CheckBox::~CheckBox()
        {
        }

        void CheckBox::Render()
        {
            switch (_style)
            {
            case Default:
                graphic::DrawRectangleLines(_coord, {_coord.x + (int)_size.x, _coord.y + (int)_size.y}, _MainColor);
                break;
            case Circle:
                graphic::DrawCircle(_coord, _size.x / 2, 36, _MainColor);
            default:
                break;
            }

            if (_status)
            {
                switch (_style)
                {
                case Default:
                    graphic::DrawRectangleFill({_coord.x + (int)_Margin, _coord.y + (int)_Margin}, {(unsigned)_size.x - (2 * _Margin), _size.y + (2 * _Margin)}, _MainColor);
                    break;
                case Circle:
                    graphic::DrawCircle({_coord.x + (int)_Margin, _coord.y + (int)_Margin}, _size.x / 2 - _Margin, 36, _MainColor);
                    break;
                case Smoth:
                    break;
                default:
                    break;
                }
            }
        }

        bool CheckBox::Handler()
        {
            if (Button::Handler()) // Если кнопка была нажата
            {
                _status != _status;
            }
            return _status;
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __CHECKBOX_H__