#include <kolibriLib/UI/buttons/TextButton.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::TextButton::TextButton(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, "Button", 16, true, ButtonColor, Margin),
		BaseButton	()
{
	#ifdef VERBOSE_DEBUG
	PrintDebug("Button contructor\n");
	#endif
}

KolibriLib::UI::buttons::TextButton::TextButton(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, text),
		BaseButton	()
{
	#ifdef VERBOSE_DEBUG
	PrintDebug("Button contructor\n");
	#endif

	SetMargin(Margin);

	_MainColor	= ButtonColor;
}

TextButton::TextButton(const TextButton &copy)
	:	TextLabel(copy),
		BaseButton(copy)
{
	PrintDebug("Button contructor(copy)\n");
}

KolibriLib::UI::buttons::TextButton::TextButton(const UDim &coord, const UDim &size, const std::string &text)
	:	TextLabel(coord, size, text),
		BaseButton()
{

}

bool KolibriLib::UI::buttons::TextButton::operator==(const TextButton &element) const
{
	return static_cast<TextLabel>(*this) == static_cast<TextLabel>(element);
}

bool KolibriLib::UI::buttons::TextButton::operator!=(const TextButton &element) const
{
	return static_cast<TextLabel>(*this) != static_cast<TextLabel>(element);
}

void buttons::TextButton::OnButtonEvent(ButtonID PressedButtonID)
{
	_status = (PressedButtonID == _id); // Если id нажатой кнопки совпадает к id этой кнопки
}

void buttons::TextButton::Render() const
{
	if(Visible)
	{
		PrintDebug("Render TextButton");

		if (IsActive())
		{
			Define(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);

			TextLabel::Render();
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
	{
		return _ButtonsIDController;
	}
	else if (Parent.lock())
	{
		return Parent.lock().get()->GetButtonIDController();
	}
	else
	{
		return nullptr;
	}
}

void KolibriLib::UI::buttons::TextButton::SetButtonIDController(const buttons::ButtonsIDController *buttonsIDController)
{
	_ButtonsIDController = const_cast<buttons::ButtonsIDController *>(buttonsIDController);
}

void KolibriLib::UI::buttons::TextButton::swap(TextLabel &a)
{
	TextButton buff(*this);

	*this = a;
	a = buff;
}

void KolibriLib::PrintDebug(const UI::buttons::TextButton &out)
{
	PrintDebug(static_cast<text::TextLabel>(out));
	PrintDebug(static_cast<buttons::BaseButton>(out));
}

