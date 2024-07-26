#include <kolibriLib/UI/UI.hpp>

#include <algorithm>

#include <input.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/graphic/screen.hpp>

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

point KolibriLib::UI::UDim::GetAbsolute(const point &Parent) const
{
	return { static_cast<int>(static_cast<float>(Parent.x) * X.Scale) + X.Offset,
	         static_cast<int>(static_cast<float>(Parent.y) * Y.Scale) + Y.Offset };
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
	:	GuiObject	(),
		_coord	(coord),
		_size	(size),
		_MainColor	(MainColor),
		_Margin	(Margin)
{

}

KolibriLib::UI::UIElement::UIElement(const UIElement &cp)
	:	GuiObject	(),
		_coord	(cp._coord),
		_size	(cp._size),
		_MainColor	(cp._MainColor),
		_Margin	(cp._Margin),
		Parent	(cp.Parent)
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

Size KolibriLib::UI::UIElement::GetAbsoluteSize() const
{
	#ifdef DEBUG
	_ksys_debug_puts("GetAbsoluteSize");
	#endif

	if(Parent != nullptr)
	{
		#ifdef DEBUG
		_ksys_debug_putc('\n');
		#endif

		return _size.GetAbsolute(Parent->GetAbsoluteSize());
	}
	else
	{
		#ifdef DEBUG
		_ksys_debug_puts("Parent no set\n");
		#endif

		return _size.GetAbsolute(window::GetWindowSize());
	}
}

Coord KolibriLib::UI::UIElement::GetAbsoluteCoord() const
{
	#ifdef DEBUG
	_ksys_debug_puts("GetAbsoluteCoord");
	#endif
	if(Parent != nullptr)
	{
		#ifdef DEBUG
		_ksys_debug_putc('\n');
		#endif

		return _coord.GetAbsolute(Parent->GetAbsoluteCoord());
	}
	else
	{
		#ifdef DEBUG
		_ksys_debug_puts("Parent no set\n");
		#endif

		return _coord.GetAbsolute(window::GetWindowCoord());
	}
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
	if(Parent != nullptr)
	{
		Coord Mouse = mouse::GetMousePositionInWindow();
		point coord	= GetAbsoluteSize();
		Size size	= GetAbsoluteSize();

		return ( (coord < Mouse)	&&
		         (Mouse.x < (coord.x + size.x)) &&
		         (Mouse.y < (coord.x + size.y)) &&
		         (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot()) );
	}

	return false;
}

int KolibriLib::UI::UIElement::Handler()
{
	//_ksys_debug_puts("call KolibriLib::UIElement, this func do nothing...\n");
	return 0;
}

void KolibriLib::UI::UIElement::SetParent(const GuiObject *NewParent)
{
	#ifdef DEBUG
	_ksys_debug_puts("SetParent\n");
	#endif

	bool a = false;
	if(NewParent->ClassName != "Window")
	{
		a = true;
		((UIElement*)	Parent)->DeleteChildren(this);
	}

	Parent =(GuiObject*) NewParent;

	if(a)
		((UIElement*)	Parent)->AddChildren(this);
}

const GuiObject *KolibriLib::UI::UIElement::GetParent() const
{
	return Parent;
}

UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
{
	_coord	= Element._coord;
	_size	= Element._size;
	_MainColor	= Element._MainColor;
	_Margin	= Element._Margin;
	Parent	= Element.Parent;
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
	graphic::DrawRectangleFill(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);
}

void KolibriLib::UI::UIElement::SetSize(const Size &NewSize)
{
	_size = UDim(NewSize);
}

void KolibriLib::UI::UIElement::SetCoord(const Coord &NewCoord)
{
	_coord = UDim(NewCoord);
}

std::vector<UIElement*> KolibriLib::UI::UIElement::GetChildren() const
{
	return _childs;
}

void KolibriLib::UI::UIElement::AddChildren(const UIElement *child)
{
	_childs.push_back((UIElement*)child);
}

void KolibriLib::UI::UIElement::DeleteChildren(const UIElement *child)
{
	auto n = std::find(_childs.begin(), _childs.end(), child);

	if(!(n == _childs.end()))
	{
		_childs.erase(n);
	}
}

