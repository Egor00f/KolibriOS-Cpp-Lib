#ifndef __FORM_H__
#define __FORM_H__

#include <string>

#include "UI.hpp"
#include "graphic.hpp"
#include "text.hpp"
#include "button.hpp"
#include "input.hpp"
#include "color.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// \brief Форма для ввода текста
        class Form : public UIElement
        {
        private:
            /// @brief Кнопка
            buttons::Button _butt;

            /// @brief Введённый пользователем текст
            std::string _inputText;

        public:
            /// \brief конструктор
            /// \param coord позиция в коне
            /// \param size размеры
            /// \param BackgroundText фоновый текст(проподает когда вводится текст)
            /// \param FormColor цвет рамки формы
            /// \param BackgroundTextColor цвет фонового текста
            /// \param Margin отступы рамки от текста
            Form(const Coord& coord = {0, 0}, const Size& size = {32, 16}, const std::string& BackgroundText = "Text...", const Color::Color& FormColor = OS::sys_color_table.work_text, const Color::Color& ButtonTextColor = OS::sys_color_table.work_area, const unsigned& Margin = DefaultMargin);

            void init(Coord coord = {0, 0}, Size size = {32, 16}, std::string BackgroundText = " ", Color::Color FormColor = OS::sys_color_table.work_text, Color::Color ButtonTextColor = OS::sys_color_table.work_area, unsigned Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void Render();

            /// \brief Обработчик
            void Handler();

            /// @brief Обработчик кнопки
            /// @return true если на форму нажали,
            bool ButtonHandler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
            std::string GetInput();

            /// @brief
            /// @return
            std::string GetBackgroundText();

            /// @brief
            /// @return
            Color::Color GetBackgroundColor();


            ~Form();
        };

        Form::Form(const Coord& coord, const Size& size, const std::string& BackgroundText, const Color::Color& FormColor, const Color::Color& ButtonTextColor, const unsigned& Margin) : UIElement(coord, size, FormColor, Margin)
        {
            #ifdef DEBUG == true
            _ksys_debug_puts("Form Constructor\n");
            #endif
            _butt.init(coord, size, " ", Margin, ButtonTextColor); // Инициализация кнопки
        }

        void Form::init(Coord coord, Size size, std::string BackgroundText, Color::Color FormColor, Color::Color ButtonTextColor, unsigned Margin)
        {
            _coord = coord;
            _size = size;
            _MainColor = FormColor;
            _Margin = Margin;
            _butt.init(coord, size, "BackgroundText", Margin, ButtonTextColor);
        }

        std::string Form::GetBackgroundText()
        {
            return _butt.GetTextLabel();
        }

        Color::Color Form::GetBackgroundColor()
        {
            return _butt.GetColor();
        }

        Form::~Form()
        {
            
        }

        void Form::Render()
        {
            graphic::DrawRectangleLines(_coord, {_coord.x + (int)_size.x, _coord.y + (int)_size.y}, _MainColor);

            _butt.Render();
        }

        std::string Form::GetInput()
        {
            return _inputText;
        }

        void Form::Handler()
        {
            char input = keyboard::CheckKeyboard();
            if (input > 33 && input != 127) // Если введённый символ не является спецсимволом, и это не Delete
            {
                _inputText.push_back(input);
            }
            if (input == 127) // input = Delete
            {
                _inputText.erase(_inputText.end() - 1);
            }
        }
        bool Form::ButtonHandler()
        {
            if (_butt.Handler())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    } // namespace UI
} // namespace KolibriLib


#endif // __FORM_H__