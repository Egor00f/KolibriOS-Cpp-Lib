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
            Form(const Coord& coord = {0, 0}, const Size& size = {32, 16}, const std::string& BackgroundText = "Text...", const Colors::Color& FormColor = OS::sys_color_table.work_text, const Colors::Color& ButtonTextColor = OS::sys_color_table.work_area, const unsigned& Margin = DefaultMargin);

            void init(Coord coord = {0, 0}, Size size = {32, 16}, std::string BackgroundText = " ", Colors::Color FormColor = OS::sys_color_table.work_text, Colors::Color ButtonTextColor = OS::sys_color_table.work_area, unsigned Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void Render();

            /// \brief Обработчик
            void Handler();

            /// @brief Обработчик кнопки
            /// @return true если на форму нажали,
            bool ButtonHandler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
            std::string GetInput() const;

            /// @brief Получить цвет фонового текста
            /// @return
            std::string GetBackgroundText() const;

            /// @brief Получить цвет фона
            /// @return
            Colors::Color GetBackgroundColor() const;

            /// @brief Изменить фоновый текст
            /// @param NewText текст
            void SetBackgroundText(const std::string& NewText);

            /// @brief Изменить цвет фона
            /// @param NewColor цвет
            void SetBackgroundColor(const Colors::Color& NewColor);

            ~Form();
        };

        
    } // namespace UI
} // namespace KolibriLib


#endif // __FORM_H__