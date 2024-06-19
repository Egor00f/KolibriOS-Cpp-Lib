#include <kolibriLib/UI/checkbox.hpp>

using namespace KolibriLib;
using namespace UI;

CheckBox::CheckBox(const UDim &coord, const UDim &size, const style &Style, const Colors::Color &CheckBoxBorderColor, const Colors::Color &BackgroundColor, const unsigned &Margin)
	: Button(coord, size, Margin, BackgroundColor), _style(Style)
{
	#if DEBUG
	_ksys_debug_puts("CheckBox Constructor\n");
	#endif
}

void CheckBox::Render()
{
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

	if (_status)
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
			_ksys_debug_puts("KolibriLib::UI::Checkbox smath style now not support :(");
			break;
		default:
			break;
		}
	}
}

int CheckBox::Handler()
{
	if (Button::Handler()) // Если кнопка была нажата
	{
		_status = !_status;
	}
	return _status;
}