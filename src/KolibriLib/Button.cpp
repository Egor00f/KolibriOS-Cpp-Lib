#include <kolibriLib/UI/buttons/button.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

Button::Button()
	:	UIElement(), 
		BaseButton()
{
	PrintDebug("Button constructor\n");
}

Button::Button(UDim coord, UDim size, unsigned Margin, Colors::Color backgrouncolor)
	:	UIElement(coord, size, backgrouncolor, Margin),
		BaseButton()
{
	PrintDebug("Button constructor\n");
}

void KolibriLib::UI::buttons::Button::Render() const
{
	BaseButton::Define(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);
}

void buttons::Button::OnButtonEvent(ButtonID PressedButtonID) 
{
	_status = PressedButtonID == _id; // Если id нажатой кнопки совпадает к id этой кнопки
}

void KolibriLib::PrintDebug(const UI::buttons::Button &out)
{
	PrintDebug(static_cast<UIElement>(out));
	PrintDebug(static_cast<BaseButton>(out));
}