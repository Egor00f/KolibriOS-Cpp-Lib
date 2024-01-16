#ifndef __FORM_H__
#define __FORM_H__

#include <string>

#include "UI.hpp"
#include "text.hpp"
#include "button.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// \brief Форма для ввода текста
        class Form : public UIElement
        {
        private:
            /// @brief Кнопка
            KolibriLib::UI::buttons::TextButton _butt;

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
            Form(point<unsigned> coord = {0, 0}, point<unsigned> size = {32, 16}, std::string BackgroundText = " ", ksys_color_t FormColor = OS::sys_color_table.work_text, ksys_color_t ButtonTextColor = OS::sys_color_table.work_area, unsigned Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void render();

            /// \brief Обработчик
            void Handler();

            /// @brief Обработчик кнопки
            /// @return true если на форму нажали,
            bool ButtonHandler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
            std::string GetInput();

            ~Form();
        };

        Form::Form(point<unsigned> coord, point<unsigned> size, std::string BackgroundText, ksys_color_t FormColor, ksys_color_t ButtonTextColor, unsigned Margin) : UIElement(coord, size, FormColor, Margin)
        {
            _butt.init(coord, size, Margin, ButtonTextColor); //Инициализация кнопки
            _butt.SetText(BackgroundText);
        }

        Form::~Form()
        {
            _butt.~TextButton();
        }

        void Form::render()
        {
            KolibriLib::graphic::DrawRectangleLines(_coord, {_coord.x + _size.x, _coord.y + _size.y}, _MainColor);

            _butt.render();
        }

        std::string Form::GetInput()
        {
            return _inputText;
        }

        void Form::Handler()
        {
            char input = CheckKeyboard();
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