#ifndef __UI_H_INCLUDE__
#define __UI_H_INCLUDE__


#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/UI/buttons/button.hpp>
#include <kolibriLib/UI/buttons/TextButton.hpp>
#include <kolibriLib/UI/buttons/ImageButton.hpp>
#include <kolibriLib/UI/checkbox.hpp>
#include <kolibriLib/UI/form.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibriLib/UI/menu.hpp>
#include <kolibriLib/UI/text/textlabel.hpp>
//#include <kolibriLib/UI/text/font.hpp>
//#include <kolibriLib/UI/text/fontslist.hpp>


namespace KolibriLib
{
	// чтоб не ипаться с этими намспейсами

	using UI::UIElement;
	using KolibriLib::UI::Images::img;
	using KolibriLib::UI::text::TextLabel;
	
	using UI::buttons::ButtonID;
	using UI::buttons::BaseButton;
	using UI::buttons::Button;
	using UI::buttons::TextButton;
	using UI::buttons::ImageButton;
	
	//using UI::text::Fonts::Font;
	//using UI::Menu;
	using UI::CheckBox;
//	using UI::Form;
	using UI::text::DrawText;
	using UI::BaseEditor;
	
} // namespace KolibriLib

#endif // __UI_H_INCLUDE__