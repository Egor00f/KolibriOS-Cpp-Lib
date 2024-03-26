#ifndef __FORM_H__
#define __FORM_H__

#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/UI/text/textlabel.hpp>
#include <kolibriLib/UI/button.hpp>
#include <input.hpp>
#include <kolibriLib/color.hpp>

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
            Form(const Coord& coord = {0, 0}, const Size& size = {32, 16}, const std::string& BackgroundText = "Text...", const Colors::Color& FormColor = OS::GetSystemColors().work_text, const Colors::Color& ButtonTextColor = OS::GetSystemColors().work_area, const unsigned& Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void Render() const;

            /// \brief Обработчик
            void Handler();

            /// @brief Обработчик кнопки
            /// @return true если на форму нажали,
            bool ButtonHandler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
            const std::string& GetInput() const;

            /// @brief Получить цвет фонового текста
            /// @return Цвет фонового текста
            const std::string& GetBackgroundText() const;

            /// @brief Получить цвет фона
            /// @return Цвет фона формы
            const Colors::Color& GetBackgroundColor() const;

            /// @brief Изменить фоновый текст
            /// @param NewText текст
            void SetBackgroundText(const std::string& NewText);

            /// @brief Изменить цвет фона
            /// @param NewColor цвет
            void SetBackgroundColor(const Colors::Color& NewColor);

            ~Form();
        };

        Form::Form(const Coord &coord, const Size &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin) : UIElement(coord, size, FormColor, Margin)
        {
            _butt.SetCoord(coord);
            _butt.SetSize(size);
            _butt.SetTextColor(ButtonTextColor);
            _butt.SetBackgroundColor(FormColor);
            _butt.Add(BackgroundText);
        }

        const std::string &Form::GetBackgroundText() const
        {
            return _butt.GetText();
        }

        const Colors::Color &Form::GetBackgroundColor() const
        {
            return _butt.GetColor();
        }

		void Form::SetBackgroundColor(const Colors::Color &NewColor)
		{
            _butt.SetColor(NewColor);
		}

		Form::~Form()
		{
        }

        void Form::Render() const
        {
            graphic::DrawRectangleLines(_coord, {_coord.x + (int)_size.x, _coord.y + (int)_size.y}, _MainColor);

            _butt.Render();
        }

        const std::string &Form::GetInput() const
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
            return _butt.Handler();
        }

        void KolibriLib::UI::Form::SetBackgroundText(const std::string &NewText)
        {
            _butt.SetText(NewText);
        }
        
    } // namespace UI
} // namespace KolibriLib


#endif // __FORM_H__