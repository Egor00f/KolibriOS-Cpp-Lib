#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "baseButton.hpp"
#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
    namespace UI
    {
        namespace buttons
        {
			/// @brief просто кнопка
			class Button: public UIElement, public BaseButton
			{
			public:
				/// @brief Конструктор по умолчанию
				Button();

                /// @brief Конструктор
                /// @param coord координаты
                /// @param size ра-змер
                /// @param Margin 
                /// @param backgrouncolor цвет фона
                Button(UDim coord, UDim size, unsigned Margin = DefaultMargin, Colors::Color backgrouncolor = Globals::SystemColors.work_button);

                /// @brief отрисовать кнопку
                void Render() const override;

                void OnButtonEvent(ButtonID PressedButtonID);

                void swap(Button& a);

                /// @brief оператор
                /// @param  
                /// @return 
                Button& operator = (const Button&) = default;

                /**
                 * @brief 
                 * @param val то с чем сравнивать
                 * @return 
                 */
                bool operator == (const Button& val) const;

                /**
                 * @brief 
                 * @param val 
                 * @return 
                 */
                bool operator != (const Button& val) const;

            private:
			};
        } // namespace buttons

    } // namespace UI

    void PrintDebug(const UI::buttons::Button &out);

} // namespace KolibriLib

#endif // __BUTTON_HPP__