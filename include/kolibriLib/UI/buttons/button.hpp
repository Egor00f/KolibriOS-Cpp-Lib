#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "baseButton.hpp"
#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с кнопками
        namespace buttons
        {
			class Button: public UIElement, public BaseButton
			{
			public:
				Button();
			private:
				
			};
        } // namespace buttons

    } // namespace UI

    void PrintDebug(const UI::buttons::Button &out);

} // namespace KolibriLib

#endif // __BUTTON_H__