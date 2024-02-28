#include <kolibriLib/UI/button.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

ButtonID buttons::GetFreeButtonId()
{
    auto p = ButtonsIdList.emplace(true);
    return p.first;
}


buttons::Button::Button(const Coord &coord, const Size &size, const unsigned& Margin, const Colors::Color& ButtonColor) : UIElement(coord, size, ButtonColor, Margin)
{
    _id = GetButtonId(GetFreeButtonId());
    _img.SetCoord(coord);
    _img.SetSize(size);
    _text.SetCoord(coord);
    _text.SetSize(size);
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
        _id = GetButtonId(GetFreeButtonId());
        _active = true;
    }
}

unsigned buttons::Button::GetType() const
{
    return _type;
}

std::string buttons::Button::GetTextLabel() const
{
    if (_type == Type::Text)
    {
        return _text.GetText();
    }
}

Images::Image buttons::Button::GetImage() const
{
    return _img;
}

void buttons::Button::SetText(const std::string &NewText)
{
    _type = Type::Text;
    _text.SetText(NewText);
}

void buttons::Button::SetImage(const Images::Image &NewImg)
{
    _type = Type::Image;
    _img = NewImg;
}

buttons::Button::~Button()
{
    DeleteButton(_id);
}

buttons::Button &KolibriLib::UI::buttons::Button::operator=(const buttons::Button &element)
{
    _coord = element._coord;
    _size = element._size;
    _MainColor = element._MainColor;
    _Margin = element._Margin;
    _id = element._id;
    _type = element._type;
    _active = element._active;

    switch (element._type)
    {
    case Type::Text:
        _text = element._text;
        break;
    case Type::Image:
        _img = element._img;
        break;
    default:
        break;
    }
    return *this;
}

bool KolibriLib::UI::buttons::Button::operator==(const Button &element) const
{
    bool r = false;
    switch (element._type)
    {
    case Type::Text:
        r = _text == element._text;
        break;
    case Type::Image:
        r = _img == element._img;
        break;
    default:
        break;
    }
    return r && (_coord == element._coord) && (_size == element._size) && (_angle == element._angle);
}

bool buttons::Button::Handler()
{
    _status = (GetPressedButton() == _id);  //Если id нажатой кнопки совпадает к id этой кнопки
    return _status;
}

bool buttons::Button::GetStatus() const
{
    return _status;
}

void buttons::Button::init(const Coord &coord, const Size &size, const std::string &text, const unsigned &Margin, const Colors::Color &ButtonColor)
{
    _coord = coord;
    _size = size;
    _Margin = Margin;

    _text.SetText(text);
    _type = Type::Text;

    _text.SetCoord(coord);
    _text.SetSize(size);
    _text.SetScale(true);

    _MainColor = ButtonColor;

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void buttons::Button::init(const Coord &coord, const Size &size, const Images::Image &image, const unsigned &Margin, const Colors::Color &ButtonColor)
{
    _coord = coord;
    _size = size;
    _Margin = Margin;

    _img = image;
    _type = Type::Image;
    _img.SetCoord(coord);
    _img.SetSize(size);

    _MainColor = ButtonColor;

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void buttons::Button::init(const Coord &coord, const Size &size, std::string Path)
{
    _coord = coord;
    _size = size;

    _img.LoadImage(Path);
    _type = Type::Image;
    _img.SetCoord(coord);
    _img.SetSize(size);

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void buttons::Button::Render() const
{
    if (_active)
    {
        buttons::DefineButton(_coord, _size, _id, _MainColor);

        switch (_type)
        {
        case Type::Image:
            _img.Render();
            break;
        case Type::Text:
            _text.Render();
            break;
        default:
            break;
        }
    }
}

buttons::ButtonID buttons::Button::GetId() const
{
    return _id;
}