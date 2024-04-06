#include <kolibriLib/UI/UI.hpp>

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::UIElement::UIElement(const Coord &coord, const Size &size, const Colors::Color &MainColor, const unsigned &Margin, bool relative)
	: _coord((Coord){coord.x, coord.y + (int)window::GetSkinHeight()}), _size(size), _MainColor(MainColor), _Margin(Margin), _relative(relative)
{
	
}

const Size &KolibriLib::UI::UIElement::GetSize() const
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

const Colors::Color &KolibriLib::UI::UIElement::GetColor() const
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

const Coord &KolibriLib::UI::UIElement::GetCoord() const
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
	Coord Mouse = mouse::GetMousePositionInWindow();

	return ((_coord.x < Mouse.x) && (_coord.y < Mouse.y) && (Mouse.x < (_coord.x + _size.x)) && (Mouse.y < (_coord.y + _size.y))) && (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
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

void KolibriLib::UI::UIElement::Render()
{
	graphic::DrawRectangleFill(_coord, _size, _MainColor);
}