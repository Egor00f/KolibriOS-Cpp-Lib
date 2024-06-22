#ifndef __FORM_H__
#define __FORM_H__

#include <string>

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/UI/text/textlabel.hpp>
#include <kolibriLib/UI/button.hpp>
#include <input.hpp>
#include <kolibriLib/color.hpp>
#include <memory>

namespace KolibriLib
{
    namespace UI
    {
        /// \brief Форма для ввода текста
        class Form : public UIElement
        {
        private:
            /// @brief Кнопка
            std::unique_ptr<buttons::Button> _butt;

            /// @brief Введённый пользователем текст
            std::string _inputText;

        public:
            std::string ClassName = "Form";
            bool RenderOnEverythingRedraw = true;

            /// \brief конструктор
            /// \param coord позиция в коне
            /// \param size размеры
            /// \param BackgroundText фоновый текст(проподает когда вводится текст)
            /// \param FormColor цвет рамки формы
            /// \param BackgroundTextColor цвет фонового текста
            /// \param Margin отступы рамки от текста
            Form(const UDim& coord = point(0), const UDim& size = DefaultSize, const std::string& BackgroundText = "Text...", const Colors::Color& FormColor = OS::GetSystemColors().gui_frame, const Colors::Color& ButtonTextColor = OS::GetSystemColors().gui_text, const unsigned& Margin = DefaultMargin);

            /// \brief Отрисовать форму
            void Render() const;

            /// \brief Обработчик
            int Handler();

            /// @brief Обработчик кнопки
            /// @return true если на форму нажали,
            bool ButtonHandler();

            /// \brief Получить введённый текст
            /// \return @link _inputText (текст который ввели в форму)
            std::string GetInput() const;

            /// @brief Получить цвет фонового текста
            /// @return Цвет фонового текста
            std::string GetBackgroundText() const;

            /// @brief Получить цвет фона
            /// @return Цвет фона формы
            Colors::Color GetBackgroundColor() const;

            /// @brief Изменить фоновый текст
            /// @param NewText текст
            void SetBackgroundText(const std::string& NewText);

            /// @brief Изменить цвет фона
            /// @param NewColor цвет
            void SetBackgroundColor(const Colors::Color& NewColor);
        };

        
        
    } // namespace UI
} // namespace KolibriLib


#endif // __FORM_H__