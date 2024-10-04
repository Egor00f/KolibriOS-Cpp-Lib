#ifndef __BASE_EDITOR_HPP__
#define __BASE_EDITOR_HPP__

#include <string>

#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/UI/buttons/TextButton.hpp>
#include <input.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/globals.hpp>
#include <kolibriLib/debug.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Форма для ввода текста
		/// @warning не завершено
        class BaseEditor : public buttons::TextButton
        {
        public:

            /// \brief конструктор
            /// \param coord позиция в коне
            /// \param size размеры
            /// \param BackgroundText фоновый текст(проподает когда вводится текст)
            /// \param FormColor цвет рамки формы
            /// \param BackgroundTextColor цвет фонового текста
            /// \param Margin отступы рамки от текста
            BaseEditor(const UDim &coord = point(0), const UDim &size = DefaultSize, const std::string &BackgroundText = "Text...", const Colors::Color &FormColor = Globals::SystemColors.work_text, const Colors::Color &ButtonTextColor = Globals::SystemColors.work_area, const unsigned &Margin = DefaultMargin);

            void OnButtonEvent(buttons::ButtonID PressedButtonID);

            void OnKeyEvent();

            /// \brief Получить введённый текст
            /// \return _inputText (текст который ввели в форму)
            std::string GetInput() const;

        private:

            std::string textBuff;

            bool Active = false;

            mutable bool textBuffStatus;
        };

        
        
    } // namespace UI

    void PrintDebug(const UI::BaseEditor &out);
} // namespace KolibriLib


#endif // __FORM_H__