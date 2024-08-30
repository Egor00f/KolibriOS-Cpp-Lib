#ifndef __TEXTBUTTON_H__
#define __TEXTBUTTON_H__

#include "baseButton.hpp"
#include <kolibriLib/UI/text/textlabel.hpp>

namespace KolibriLib
{
	namespace UI
	{
		namespace buttons
		{
			 /// \brief Класс для работы с кнопками
            class TextButton: public text::TextLabel, public BaseButton
            {
            public:

                bool RenderOnEverythingRedraw = true;

                /// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
				TextButton(const UDim &coord = point(0), const UDim &size = DefaultSize, unsigned Margin = UI::DefaultMargin, const Colors::Color &ButtonColor = Globals::SystemColors.work_button);

				/// \brief Это конструктор
                /// \param coord координата
                /// \param size размер
                /// \param text текст
                /// \param Margin отступы текста от границ
                /// \param ButtonColor цвет кнопки
                /// \param TextColor цвет текста
               TextButton(const Txt &text, const UDim &coord = point(0), const UDim &size = DefaultSize, unsigned Margin = UI::DefaultMargin, const Colors::Color &ButtonColor = Globals::SystemColors.work_button);

                /// @brief Конструктор копирования
                /// @param copy Кнопка которую будут копировать
			   TextButton(const TextButton &copy);

			   /// @brief Отрисовать кнопку
			   void Render() const;

			   /// @brief Обработчик кнопки
			   /// @return Состояние кнопки(Нажата/Ненажата)
			   /// @details устанавливает переменную _status в true если эта кнопка нажата, иначе false
			   /// @note Эту функцию нужно вызывать в цикле, чтобы кнопка работала
			   void OnButtonEvent(ButtonID PressedButtonID);

			   buttons::ButtonsIDController *GetButtonIDController() const;

			   void SetButtonIDController(const buttons::ButtonsIDController *buttonsIDController);

			   TextButton &operator=(const TextButton &element);

			   bool operator==(const TextButton &element) const;

		   private:

            };
		}
	}

	void PrintDebug(const UI::buttons::TextButton &out);
}

#endif // __TEXTBUTTON_H__