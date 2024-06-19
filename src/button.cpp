#include <kolibriLib/UI/checkbox.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::Button::Button(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	: TextLabel(coord, size, "Button", 16, true, OS::GetSystemColors().gui_text, Margin), _id(GetFreeButtonId())
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif
}

KolibriLib::UI::buttons::Button::Button(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	: TextLabel(coord, size, text)
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif
}

Button::Button(const Button &copy)
	: TextLabel(copy), _id(copy._id)
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor(copy)\n");
	#endif
}

void buttons::Button::Deactivate()
{
	if (_active)
	{
		DeleteButton(_id);
		_active = false;
	}
}

void buttons::Button::Activate()
{
	if (!_active)
	{
		_id = GetFreeButtonId();
		_active = true;
	}
}

buttons::Button::~Button()
{
	DeleteButton(_id);
}

buttons::Button &KolibriLib::UI::buttons::Button::operator=(const buttons::Button &element)
{
	_coord	= element._coord;
	_size	= element._size;
	_MainColor	= element._MainColor;
	_Margin	= element._Margin;
	_id	= element._id;
	_active	= element._active;
	_data	= element._data;

	return *this;
}

bool KolibriLib::UI::buttons::Button::operator==(const Button &element) const
{

	return (_data == element._data)	&&
		   (_coord == element._coord)	&&
		   (_size == element._size);
}

int buttons::Button::Handler()
{
	_status = GetPressedButton() == _id; // Если id нажатой кнопки совпадает к id этой кнопки
	return _status;
}

bool buttons::Button::GetStatus() const
{
	return _status;
}

void buttons::Button::Render() const
{
	if (_active)
	{
		buttons::DefineButton(_coord.GetAbsolute(), _size.GetAbsolute(), _id, _MainColor);

		Print(Coord(_coord.GetAbsolute().x + ((int)_size.GetAbsolute().x / 2), 
		            _coord.GetAbsolute().y + ((int)_size.GetAbsolute().y / 2)));
	}
}

buttons::ButtonID buttons::Button::GetId() const
{
	return _id;
}