#include <kolibriLib/UI/button.hpp>
#include <kolibriLib/globals.hpp>


using namespace KolibriLib;
using namespace UI;
using namespace buttons;

buttons::Button::Button(const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, "Button", 16, true, ButtonColor, Margin)
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif

	if(KolibriLib::Globals::DefaultButtonsIDController != nullptr)
	{
		_ButtonsIDController = KolibriLib::Globals::DefaultButtonsIDController;
		_id = KolibriLib::Globals::DefaultButtonsIDController->GetFreeButtonID();
	}
}

KolibriLib::UI::buttons::Button::Button(const Txt &text, const UDim &coord, const UDim &size, unsigned Margin, const Colors::Color &ButtonColor)
	:	TextLabel	(coord, size, text)
{
	#ifdef DEBUG
	_ksys_debug_puts("Button contructor\n");
	#endif

	SetMargin(Margin);

	_MainColor	= ButtonColor;

	if (KolibriLib::Globals::DefaultButtonsIDController != nullptr)
	{
		_ButtonsIDController = KolibriLib::Globals::DefaultButtonsIDController;
		_id = KolibriLib::Globals::DefaultButtonsIDController->GetFreeButtonID();
	}
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
	if (_active && _id != buttons::ButtonIDNotSet)
	{
		if(_ButtonsIDController != nullptr)
		{
			_ButtonsIDController->FreeButtonID(_id);
		}
		DeleteButton(_id);

		_id = buttons::ButtonIDNotSet;

		_active = false;
	}
}

void buttons::Button::Activate()
{
	if (!_active)
	{
		_id	= _ButtonsIDController->GetFreeButtonID();
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
	SetMargin(element.GetMargin());
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
	#ifdef DEBUG
	_ksys_debug_puts("Render Button:");
	#endif

	if (_active)
	{
		buttons::DefineButton(GetAbsoluteCoord(), GetAbsoluteSize(), _id, _MainColor);

		//TextLabel::Render();
	}

	#ifdef DEBUG
	_ksys_debug_puts("done\n");
	#endif
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


buttons::ButtonsIDController *KolibriLib::UI::buttons::Button::GetButtonIDController() const
{
	if (_ButtonsIDController != nullptr)
	{
		return _ButtonsIDController;
	}
	else if(Parent != nullptr)
	{
		return Parent->GetButtonIDController();
	}
	else
	{
		return nullptr;
	}
}

void KolibriLib::UI::buttons::Button::SetButtonIDController(const buttons::ButtonsIDController* buttonsIDController) 
{
	_ButtonsIDController = (buttons::ButtonsIDController*)buttonsIDController;
}