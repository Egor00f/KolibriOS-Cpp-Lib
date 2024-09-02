#include <kolibriLib/UI/buttons/TextButton.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::TextButton::TextButton(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, "Button", 16, true, ButtonColor, Margin),
		BaseButton	()
{
	PrintDebug("Button contructor\n");

	
}

KolibriLib::UI::buttons::TextButton::TextButton(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, text),
		BaseButton	()
{
	PrintDebug("Button contructor\n");

	SetMargin(Margin);

	_MainColor	= ButtonColor;

	
}

TextButton::TextButton(const TextButton &copy)
	:	TextLabel(copy),
		BaseButton(copy._id)
{
	PrintDebug("Button contructor(copy)\n");
}

buttons::TextButton &KolibriLib::UI::buttons::TextButton::operator=(const buttons::TextButton &element)
{
	_coord	= element._coord;
	_size	= element._size;
	_data	= element._data;
	_MainColor	= element._MainColor;
	SetMargin(element.GetMargin());
	_id	= element._id;
	
	return *this;
}

bool KolibriLib::UI::buttons::TextButton::operator==(const TextButton &element) const
{
	return (_data	== element._data)  &&
		   (_coord	== element._coord) &&
		   (_size	== element._size)  &&
		   (_data	== element._data)  &&
		   (_MainColor	== element._MainColor) &&
		   (GetMargin() == element.GetMargin());
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
	else if (Parent != nullptr)
	{
		return Parent->GetButtonIDController();
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

void KolibriLib::PrintDebug(const UI::buttons::TextButton &out)
{
	PrintDebug(static_cast<text::TextLabel>(out));
	PrintDebug(static_cast<buttons::BaseButton>(out));
}

