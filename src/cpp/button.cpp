#include <kolibriLib/UI/button.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

ButtonID buttons::GetFreeButtonId()
{
    for(unsigned i = 0; i < ButtonsIdList.size(); i++)
    {
        if(ButtonsIdList.count(i) == 0)
        {
            return i + StartButtonId;
        }
    }
}


buttons::Button::Button(const Coord &coord, const Size &size, unsigned Margin, const Colors::Color& ButtonColor) : TextLabel(coord, size, NULL, NULL, true, NULL, Margin)
{
    _id = GetFreeButtonId();
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
    _coord      = element._coord;
    _size       = element._size;
    _MainColor  = element._MainColor;
    _Margin     = element._Margin;
    _id         = element._id;
    _active     = element._active;
    _data       = element._data;

    return *this;
}

bool KolibriLib::UI::buttons::Button::operator==(const Button &element) const
{
    
    return (_data == element._data) && 
        (_coord == element._coord) && 
        (_size == element._size) && 
        (_angle == element._angle);
}

bool buttons::Button::Handler() const
{
    _status = GetPressedButton() == _id;  //Если id нажатой кнопки совпадает к id этой кнопки
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
        buttons::DefineButton(_coord, _size, _id, _MainColor);

        Print({_coord.x + ((int)_size.x/2), _coord.y + ((int)_size.y/2)});
    }
}

buttons::ButtonID buttons::Button::GetId() const
{
    return _id;
}