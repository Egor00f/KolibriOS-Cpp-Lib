#include <kolibriLib/UI/buttons/TextButton.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::TextButton::TextButton(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	Button	(coord, size, Margin, ButtonColor),
		Txt("Button")
{
	#ifdef VERBOSE_DEBUG
	PrintDebug("Button contructor\n");
	#endif
}

KolibriLib::UI::buttons::TextButton::TextButton(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	Button	(coord, size, Margin, ButtonColor),
		Txt(text)
{
	#ifdef VERBOSE_DEBUG
	PrintDebug("Button contructor\n");
	#endif

	SetMargin(Margin);

	_MainColor	= ButtonColor;
}

KolibriLib::UI::buttons::TextButton::TextButton(const UDim &coord, const UDim &size, const std::string &text)
	:	Button(coord, size),
		Txt(text)
{
}

bool KolibriLib::UI::buttons::TextButton::operator==(const TextButton &element) const
{
	return static_cast<Button>(*this) == static_cast<Button>(element)	&&
	       static_cast<Txt>(*this) == static_cast<Txt>(element);
}

bool KolibriLib::UI::buttons::TextButton::operator!=(const TextButton &element) const
{
	return static_cast<Button>(*this) != static_cast<Button>(element)	||
	       static_cast<Txt>(*this) != static_cast<Txt>(element);
}

bool buttons::TextButton::OnButtonEvent(ButtonID PressedButtonID)
{
	_status = (PressedButtonID == _id); // Если id нажатой кнопки совпадает к id этой кнопки
	return _status;
}

void buttons::TextButton::Render() const
{
	if(Visible)
	{
		PrintDebug("Render TextButton");

		if (IsActive())
		{
			Button::Render();
			Txt::Print(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);
		}
		else
		{
			PrintDebug(": Button Is not Active");
		}

		PrintDebug("\n");
	}
}

buttons::ButtonsIDController *KolibriLib::UI::buttons::TextButton::GetButtonIDController() const
{
	if (_ButtonsIDController != nullptr)
		return _ButtonsIDController;
	else if (std::shared_ptr<GuiObject> s_ptr = Parent.lock())
		return s_ptr->GetButtonIDController();
	else
		return nullptr;
}

void KolibriLib::UI::buttons::TextButton::SetButtonIDController(const buttons::ButtonsIDController *buttonsIDController)
{
	_ButtonsIDController = const_cast<buttons::ButtonsIDController *>(buttonsIDController);
}

void KolibriLib::UI::buttons::TextButton::swap(TextButton &a)
{
	TextButton buff(*this);

	*this = a;
	a = buff;
}

void KolibriLib::PrintDebug(const UI::buttons::TextButton &out)
{
	PrintDebug(static_cast<text::Txt>(out));
	PrintDebug(static_cast<buttons::Button>(out));
}

