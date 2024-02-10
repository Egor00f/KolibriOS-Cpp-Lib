#include "UI.hpp"

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::UIElement::UIElement(const Coord & coord, const Size & size, const Colors::Color & MainColor, const unsigned & Margin, bool relative)
{
#if DEBUG == true
    _ksys_debug_puts("UIElement:");
#endif
    _coord = (Coord){coord.x, coord.y + window::GetSkinHeight()};
    _size = size;
    _MainColor = MainColor;
    _Margin = Margin;
    _relative = relative;
}

Size KolibriLib::UI::UIElement::GetSize() const
{
    return _size;
}

void KolibriLib::UI::UIElement::SetSize(const Size &NewSize)
{
    _size = NewSize;
}

unsigned KolibriLib::UI::UIElement::GetMargin() const
{
    return _Margin;
}

Colors::Color KolibriLib::UI::UIElement::GetColor() const
{
    return _MainColor;
}

void KolibriLib::UI::UIElement::SetColor(const Colors::Color &NewColor)
{
    _MainColor = NewColor;
}

void KolibriLib::UI::UIElement::SetCoord(const Coord &NewCoord)
{
    _coord = NewCoord;
}

Coord KolibriLib::UI::UIElement::GetCoord() const
{
    return _coord;
}

void KolibriLib::UI::UIElement::Rotate(unsigned NewAngle)
{
    _angle = NewAngle;
}

unsigned KolibriLib::UI::UIElement::GetRotate() const
{
    return _angle;
}

bool KolibriLib::UI::UIElement::Hover() const
{
    Coord mouse = mouse::GetMousePositionInWindow();

    return (_coord.x < mouse.x) && (_coord.y < mouse.y) && (mouse.x < (_coord.x + _size.x)) && (mouse.y < (_coord.y + _size.y));
}

UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
{
    _coord = Element._coord;
    _size = Element._size;
    _MainColor = Element._MainColor;
    _Margin = Element._Margin;
    _angle = Element._angle;
    return *this;
}

bool KolibriLib::UI::UIElement::operator==(const UIElement &Element) const
{
    return (_coord == Element._coord) && (_size == Element._size) && (_MainColor == Element._MainColor) && (_angle == Element._angle);
}

bool KolibriLib::UI::UIElement::operator!=(const UIElement &Element) const
{
    return (_coord != Element._coord) || (_size != Element._size) || (_MainColor != Element._MainColor) || (_angle != Element._angle);
}