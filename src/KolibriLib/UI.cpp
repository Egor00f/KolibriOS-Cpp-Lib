#include <kolibriLib/UI/UI.hpp>

#include <algorithm>

#include <input.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/img.hpp>

using namespace KolibriLib;
using namespace UI;

unsigned KolibriLib::UI::GuiObject::GetMargin() const
{
	return _Margin;
}

void KolibriLib::UI::GuiObject::SetMargin(unsigned NewMargin)
{
	_Margin = NewMargin;
}

KolibriLib::UI::UIElement::UIElement(const UDim &coord, const UDim &size, const Colors::Color &MainColor, const unsigned &Margin)
	:	GuiObject	(),
		_coord	(coord),
		_size	(size),
		_MainColor	(MainColor)
{
	SetMargin(Margin);
}

KolibriLib::UI::UIElement::UIElement(const UIElement &cp)
	:	GuiObject	(),
		_coord	(cp._coord),
		_size	(cp._size),
		_MainColor	(cp._MainColor),
		Parent	(cp.Parent)
{
	SetMargin(cp.GetMargin());
}

UDim KolibriLib::UI::UIElement::GetSize() const
{
	return _size;
}

void KolibriLib::UI::UIElement::SetSize(const UDim &NewSize)
{
	_size = NewSize;
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
	if (Parent.lock())
	{
		return _size.GetAbsolute(Parent.lock().get()->GetAbsoluteSize());
	}
	else
	{
		return _size.GetAbsolute(window::GetWindowSize());
	}
}

Coord KolibriLib::UI::UIElement::GetAbsoluteCoord() const
{
	if (Parent.lock())
	{
		if(ParentIsWindow)
			return (_coord.GetAbsolute(Parent.lock()->GetAbsoluteSize()));
		else
			return (_coord.GetAbsolute(Parent.lock()->GetAbsoluteSize()) + Parent.lock()->GetAbsoluteCoord());
	}
	else
	{
		return _coord.GetAbsolute(window::GetWindowSize());
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
	if (Parent.lock())
	{
		const Coord Mouse	= mouse::GetMousePositionInWindow();
		const point coord	= GetAbsoluteSize();
		const Size size 	= GetAbsoluteSize();

		return ( (coord < Mouse)	&&
		         (Mouse.x < (coord.x + size.x)) &&
		         (Mouse.y < (coord.x + size.y)) &&
		         (ScreenPointAffiliation(Mouse) == Thread::GetThreadSlot()) );
	}

	return false;
}

int KolibriLib::UI::UIElement::Handler(OS::Event)
{
	//_ksys_debug_puts("call KolibriLib::UIElement, this func do nothing...\n");
	return 0;
}

void KolibriLib::UI::UIElement::OnButtonEvent(buttons::ButtonID)
{
	
}

void KolibriLib::UI::UIElement::OnKeyEvent()
{
	
}

void KolibriLib::UI::UIElement::OnMouseEvent()
{
	
}

void KolibriLib::UI::UIElement::SetParent(const UIElement *NewParent) const
{
	PrintDebug("SetParent\n");

	if (!ParentIsWindow && Parent.lock())
	{
		((UIElement*) Parent.lock().get())->DeleteChildren(this);
	}

	std::shared_ptr<GuiObject> ptr(const_cast<GuiObject*>(static_cast<const GuiObject*>(NewParent)));

	Parent.lock().swap(ptr);

	((UIElement*) Parent.lock().get())->AddChildren(this);

	ParentIsWindow = false;
}

void KolibriLib::UI::UIElement::SetParent(std::weak_ptr<UIElement> ptr) const
{
	SetParent(ptr.lock().get());
}

void KolibriLib::UI::UIElement::WindowAsParent(const GuiObject *window) const
{
	if (!ParentIsWindow && Parent.lock())
	{
		((UIElement*) Parent.lock().get())->DeleteChildren(this);
	}

	Parent.lock().reset(const_cast<GuiObject*>(window));
	ParentIsWindow = true;
}

const GuiObject *KolibriLib::UI::UIElement::GetParent() const
{
	return Parent.lock().get();
}

UIElement &KolibriLib::UI::UIElement::operator=(const UIElement &Element)
{
	_coord	= Element._coord;
	_size	= Element._size;
	_MainColor	= Element._MainColor;
	Parent	= Element.Parent;
	Visible	= Element.Visible;
	_Margin = Element._Margin;

	return *this;
}

bool KolibriLib::UI::UIElement::operator==(const UIElement &Element) const
{
	return (_coord     == Element._coord)	&&
	       (_size      == Element._size)	&&
	       (_MainColor == Element._MainColor)	&&
	       (Visible    == Element.Visible) &&
		   (_Margin    == Element._Margin);
}

bool KolibriLib::UI::UIElement::operator!=(const UIElement &Element) const
{
	return (_coord     != Element._coord)	||
	       (_size      != Element._size)	||
	       (_MainColor != Element._MainColor)	||
	       (Visible    != Element.Visible) ||
		   (_Margin    != Element._Margin);
}

void KolibriLib::UI::UIElement::Render() const
{
	if(_MainColor)
	{
		Images::img img(_MainColor, GetAbsoluteSize(), Images::img::BPP::RGBA);
		
		img.Draw(GetAbsoluteCoord());
	}
	else
	{
		graphic::DrawRectangleFill(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);
	}
}

void KolibriLib::UI::UIElement::SetSize(const Size &NewSize)
{
	_size = UDim(NewSize);
}

void KolibriLib::UI::UIElement::SetCoord(const Coord &NewCoord)
{
	_coord = UDim(NewCoord);
}

std::vector<std::weak_ptr<UIElement>> KolibriLib::UI::UIElement::GetChildren() const
{
	return _childs;
}

std::vector<std::weak_ptr<UIElement>>& KolibriLib::UI::UIElement::GetChildren()
{
	return _childs;
}

void KolibriLib::UI::UIElement::AddChildren(const UIElement *child) const
{
	_childs.push_back(std::shared_ptr<UIElement>(const_cast<UIElement*>(child)));
}

void KolibriLib::UI::UIElement::DeleteChildren(const UIElement* child) const
{
	std::shared_ptr<UIElement> ptr(const_cast<UIElement*>(child));
	std::weak_ptr<UIElement> v = ptr;
	auto n = std::find_if
        (
            _childs.begin(), _childs.end(),
            [&v](const std::weak_ptr<UIElement>& our_obj)
            {
                return v.lock() == our_obj.lock();
            }
        );

	if(n != _childs.end())
	{
		_childs.erase(n);
	}
}

buttons::ButtonsIDController *KolibriLib::UI::UIElement::GetButtonIDController() const
{
	if(Parent.lock())
	{
		return Parent.lock().get()->GetButtonIDController();
	}
	else
	{
		return nullptr;
	}
}

void KolibriLib::UI::UIElement::SetButtonIDController(const buttons::ButtonsIDController*) 
{

}

void KolibriLib::UI::UIElement::swap(UIElement &e)
{
	UIElement buff(*this);

	*this = e;
	e = buff;
}

void KolibriLib::PrintDebug(const UI::UIElement &out)
{
	PrintDebug("UIElement:\n");
	DebugOut(":\n");
	PrintDebug(out.GetColor());
	DebugOut("\n Size:\n ");
	PrintDebug(out.GetSize());
	DebugOut("Coord:\n ");
	PrintDebug(out.GetCoord());
}