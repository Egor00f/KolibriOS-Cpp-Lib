#include <kolibriLib/UI/checkbox.hpp>
#include <kolibriLib/graphic/graphic.hpp>

using namespace KolibriLib;
using namespace UI;

CheckBox::CheckBox(const UDim &coord, const UDim &size, const style &Style, const Colors::Color &CheckBoxBorderColor, const Colors::Color &BackgroundColor, const unsigned &Margin)
	:	Button(coord, size, Margin, BackgroundColor), 
		_BorderColor(CheckBoxBorderColor),
		_style(Style)
{
	PrintDebug("CheckBox Constructor\n");
}

KolibriLib::UI::CheckBox::CheckBox(const CheckBox &a)
	:	Button(a),
		_BorderColor(a._BorderColor),
		_style(a._style),
		checked(a.checked)
{
	PrintDebug("CheckBox Constructor(copy)\n");
}

void KolibriLib::UI::CheckBox::DrawBorder() const
{
	const Coord absCoord = GetAbsoluteCoord();
	const Coord absSize = GetAbsoluteSize();

	switch (_style)
	{
	case style::Default:
		graphic::DrawRectangleLines(absCoord, absCoord + absSize, _BorderColor);
		break;
	case style::Circle:
		graphic::DrawCircle(absCoord + point(absSize.x / 2, absSize.y / 2), static_cast<unsigned int>(absSize.x) / 2, _BorderColor);
		break;
	default:
		break;
	}
}

bool KolibriLib::UI::CheckBox::GetChecked() const
{
	return checked;
}

bool KolibriLib::UI::CheckBox::OnButtonEvent(buttons::ButtonID PressedButtonID)
{
	bool ret = Button::OnButtonEvent(PressedButtonID);

	if(_status)
		checked = !checked;

	return ret;
}

void CheckBox::Render() const
{
	if(Visible)
	{
		PrintDebug("Render Checkbox\n");

		DrawBorder();

		const Coord absoluteCoord = GetAbsoluteCoord();
		const Size absoluteSize = GetAbsoluteSize();

		if (checked)
		{
			PrintDebug("CHECKOBOS IS CHECKED\n");
			
			switch (_style)
			{
			case CheckBox::style::Default:
				graphic::DrawRectangleFill(absoluteCoord + static_cast<int>(GetMargin()),
										   absoluteSize - static_cast<int>(GetMargin() * 2U),
										   _BorderColor);
				break;
			case CheckBox::style::Circle:
				graphic::DrawCircle(absoluteCoord + point(absoluteSize.x / 2, absoluteSize.y / 2),
									static_cast<unsigned int>(absoluteSize.x / 2) - GetMargin(),
									_BorderColor);
				break;
			case CheckBox::style::Smoth:
				PrintDebug("KolibriLib::UI::Checkbox smath style now not support :(\n");
				break;
			default:
				break;
			}
		}

		Button::Render();
	}
}

void KolibriLib::UI::CheckBox::SetStyle(style s)
{
	_style = s;
}

void KolibriLib::UI::CheckBox::SetBorderColor(const Colors::Color &NewBorderColor)
{
	_BorderColor = NewBorderColor;
}

Colors::Color KolibriLib::UI::CheckBox::GetBorderColor() const
{
	return _BorderColor;
}

void KolibriLib::UI::CheckBox::swap(CheckBox &a)
{
	CheckBox buff(*this);

	*this = a;
	a = buff;
}

bool KolibriLib::UI::CheckBox::operator==(const CheckBox &c) const
{
	return static_cast<buttons::Button>(*this) == static_cast<buttons::Button>(c) &&
	       (_BorderColor == c._BorderColor) &&
		   (_style == c._style);
}

bool KolibriLib::UI::CheckBox::operator!=(const CheckBox &c) const
{
	return static_cast<buttons::Button>(*this) != static_cast<buttons::Button>(c) ||
	       (_BorderColor != c._BorderColor) ||
		   (_style != c._style);
}