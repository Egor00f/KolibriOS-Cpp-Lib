#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/system/thread.hpp>

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::UDim::UDim(const point &p)
{
	X.Offset = p.x;
	Y.Offset = p.y;
}

KolibriLib::UI::UDim::UDim(float XScale, int XOffset, float YScale, int YOffset)
	: X(XScale, XOffset), Y(YScale, YOffset)
{
	
}

KolibriLib::UI::UDim::Axis::Axis(float scale, int offset)
	: Scale(scale), Offset(offset)
{
}

bool UI::UDim::Axis::operator==(const UDim::Axis &axis) const
{
	return Scale == axis.Scale && Offset == axis.Offset;
}

bool UI::UDim::Axis::operator!=(const UDim::Axis &axis) const
{
	return Scale != axis.Scale || Offset != axis.Offset;
}

point KolibriLib::UI::UDim::GetAbsolute() const
{
	Thread::ThreadInfo Info = Thread::GetThreadInfo();
	return { static_cast<int>(static_cast<float>(Info.winx_size) * X.Scale) + X.Offset, 
	         static_cast<int>(static_cast<float>(Info.winy_size) * Y.Scale) + Y.Offset };
}

bool KolibriLib::UI::UDim::operator==(const UDim &obj) const
{
	return X == obj.X && Y == obj.Y;
}

bool KolibriLib::UI::UDim::operator!=(const UDim &obj) const
{
	return X != obj.X || Y != obj.Y;
}

KolibriLib::UI::UIElement::UIElement(const UDim &coord, const UDim &size, const Colors::Color &MainColor, const unsigned &Margin)
	: _coord(coord), _size(size), _MainColor(MainColor), _Margin(Margin)
{
}

UDim KolibriLib::UI::UIElement::GetSize() const
{
	return _size;
}

void KolibriLib::UI::UIElement::SetSize(const UDim &NewSize)
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

void KolibriLib::UI::UIElement::SetCoord(const UDim &NewCoord)
{
	_coord = NewCoord;
}

UDim KolibriLib::UI::UIElement::GetCoord() const
{
	return _coord;
}

void KolibriLib::UI::UIElement::Rotate(unsigned NewAngle)
{
	_rotation = NewAngle;
}

unsigned KolibriLib::UI::UIElement::GetRotate() const
{
	return _rotation;
}

bool KolibriLib::UI::UIElement::Hover() const
{
	Coord Mouse = mouse::GetMousePositionInWindow();

	point coord	= _coord.GetAbsolute();
	Size size = _size.GetAbsolute();

	return ((coord < Mouse)	&&
			(Mouse.x < (coord.x + size.x))	&&
			(Mouse.y < (coord.x + size.y)))	&&
		   (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot(Thread::GetThreadInfo().pid));
}

UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
{
	_coord	= Element._coord;
	_size	= Element._size;
	_MainColor	= Element._MainColor;
	_Margin	= Element._Margin;
	return *this;
}

bool KolibriLib::UI::UIElement::operator==(const UIElement &Element) const
{
	return (_coord     == Element._coord)	&& 
	       (_size      == Element._size)	&& 
		   (_MainColor == Element._MainColor);
}

bool KolibriLib::UI::UIElement::operator!=(const UIElement &Element) const
{
	return (_coord     != Element._coord)	|| 
	       (_size      != Element._size)	|| 
		   (_MainColor != Element._MainColor);
}

void KolibriLib::UI::UIElement::Render() const
{
	graphic::DrawRectangleFill(_coord.GetAbsolute(), _size.GetAbsolute(), _MainColor);
}

Size KolibriLib::UI::UIElement::GetAbsoluteSize() const
{
	return _size.GetAbsolute();
}

Coord KolibriLib::UI::UIElement::GetAbsolutePos() const
{
	return _coord.GetAbsolute();
}