#include <kolibriLib/UI/button.hpp>



using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::Button::Button(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel(coord, size, "Button", 16, true, ButtonColor, Margin),
		_id(GetFreeButtonId())
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif
}

KolibriLib::UI::buttons::Button::Button(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel(coord, size, text)
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif

	_Margin	= Margin;
	_MainColor	= ButtonColor;
}

Button::Button(const Button &copy)
	:	TextLabel(copy),
		_id(copy._id)
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
		_id	= GetFreeButtonId();
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

	return (_data	== element._data)	&&
		   (_coord	== element._coord)	&&
		   (_size	== element._size)	&&
		   (_data	== element._data);
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
		const Coord COORD = GetAbsoluteCoord();
		const Size SIZE = GetAbsoluteSize();

		buttons::DefineButton(COORD, SIZE, _id, _MainColor);

		Print( Coord(COORD.x + ((int)SIZE.x / 2),
		             COORD.y + ((int)SIZE.y / 2)) );
	}
}

buttons::ButtonID buttons::Button::GetId() const
{
	return _id;
}


void KolibriLib::UI::buttons::Button::SetId(const ButtonID &NewID)
{
	Deactivate();
	_active = true;
	_id	= NewID;
}

void KolibriLib::UI::buttons::Button::SetId()
{
	Deactivate();
	Activate();
}
