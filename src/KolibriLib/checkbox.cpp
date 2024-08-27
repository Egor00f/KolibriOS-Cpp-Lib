#include <kolibriLib/UI/checkbox.hpp>

using namespace KolibriLib;
using namespace UI;

CheckBox::CheckBox(const UDim &coord, const UDim &size, const style &Style, const Colors::Color &CheckBoxBorderColor, const Colors::Color &BackgroundColor, const unsigned &Margin)
	:	TextButton(coord, size, Margin, BackgroundColor), 
		_style(Style)
{
	PrintDebug("CheckBox Constructor\n");
}

void CheckBox::Render()
{
	PrintDebug("Render Checkbox\n");

	switch (_style)
	{
	case Default:
		//graphic::DrawRectangleLines(_coord, {_coord.x + (int)_size.x, _coord.y + (int)_size.y}, _MainColor);
		break;
	case Circle:
		//graphic::DrawCircle(_coord, _size.x / 2, _MainColor);
	default:
		break;
	}

	if (GetStatus())
	{
		switch (_style)
		{
		case CheckBox::style::Default:
			//graphic::DrawRectangleFill(Coord(_coord.x + _Margin, _coord.y + _Margin),
			//						   Size(_size.x - (2 * _Margin), _size.y + (2 * _Margin)),
			//						   _MainColor);
			break;
		case CheckBox::style::Circle:
			//graphic::DrawCircle(Coord(_coord.x + _Margin, _coord.y + _Margin),
			//					_size.x / 2 - _Margin,
			//					_MainColor);
			break;
		case CheckBox::style::Smoth:
			PrintDebug("KolibriLib::UI::Checkbox smath style now not support :(\n");
			break;
		default:
			break;
		}
	}

	TextButton::Render();
}
