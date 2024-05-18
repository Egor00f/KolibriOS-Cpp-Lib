#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/system/thread.hpp>

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::UDim::UDim(const point &p)
	: Offset(p), Scale(0)
{
}

point KolibriLib::UI::UDim::AbsoluteSize()
{
	Thread::ThreadInfo Info = Thread::GetThreadInfo();
	return { (Info.winx_size * Scale.x) + Offset.x, 
	         (Info.winy_size * Scale.y) + Offset.y };
}

KolibriLib::UI::UIElement::UIElement(const UDim &coord, const UDim &size, const Colors::Color &MainColor, const unsigned &Margin, bool relative)
	: _coord(coord), _size(size), _MainColor(MainColor), _Margin(Margin)
{
	_coord.Offset.y += window::GetSkinHeight();
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

	return ((_coord.AbsoluteSize() < UDim(Mouse).AbsoluteSize())	&&
			(Mouse.x < (_coord.AbsoluteSize().x + _size.AbsoluteSize().x))	&&
			(Mouse.y < (_coord.AbsoluteSize().x + _size.AbsoluteSize().y)))	&&
		   (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot(Thread::GetThreadInfo().pid));
}

UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
{
	_coord = Element._coord;
	_size = Element._size;
	_MainColor = Element._MainColor;
	_Margin = Element._Margin;
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

void KolibriLib::UI::UIElement::Render()
{
	graphic::DrawRectangleFill(_coord.AbsoluteSize(), _size.AbsoluteSize(), _MainColor);
}