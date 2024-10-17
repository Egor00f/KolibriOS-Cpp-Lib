#include <kolibriLib/UI/buttons/button.hpp>
#include <kolibriLib/globals.hpp>


using namespace KolibriLib;
using namespace UI;
using namespace buttons;

BaseButton::BaseButton()
{
	if (KolibriLib::Globals::DefaultButtonsIDController != nullptr)
	{
		_ButtonsIDController = KolibriLib::Globals::DefaultButtonsIDController;

		std::shared_ptr<BaseButton> s_ptr(this);

		_id = KolibriLib::Globals::DefaultButtonsIDController->GetFreeButtonID(s_ptr);
	}
}

BaseButton::BaseButton(ButtonID id)
{
	if (KolibriLib::Globals::DefaultButtonsIDController != nullptr)
	{
		_ButtonsIDController = KolibriLib::Globals::DefaultButtonsIDController;
	}

	SetId(id);
}

KolibriLib::UI::buttons::BaseButton::BaseButton(const BaseButton &button)
	:	_ButtonsIDController(button._ButtonsIDController),
		_type(button._type)
{
	SetId(button._id);
}

buttons::BaseButton::~BaseButton()
{
	Deactivate();
}

void BaseButton::BaseButton::Deactivate()
{
	if (IsActive())
	{
		if(_ButtonsIDController != nullptr)
		{
			_ButtonsIDController->FreeButtonID(_id);
		}

		_id = buttons::ButtonIDNotSet;
	}
	else
	{
		PrintDebug("BaseButton already not active\n");
	}
}

void BaseButton::BaseButton::Activate()
{
	if (!IsActive())
	{
		SetId();
	}
	else
	{
		PrintDebug("BaseButton already active\n");
	}
}

bool KolibriLib::UI::buttons::BaseButton::IsActive() const
{
	return _id != ButtonIDNotSet;
}

bool buttons::BaseButton::GetStatus() const
{
	return _status;
}

buttons::ButtonID buttons::BaseButton::GetId() const
{
	return _id;
}

void KolibriLib::UI::buttons::BaseButton::SetId(const ButtonID &NewID)
{
	PrintDebug("SetId(ButtonID)\n");
	
	_id = NewID;

	if(_ButtonsIDController != nullptr)
	{
		std::shared_ptr<BaseButton> s_ptr(this);
		_ButtonsIDController->TakeupButtonID(NewID, s_ptr);
	}
}

void KolibriLib::UI::buttons::BaseButton::SetId()
{
	PrintDebug("SetId()\n");

	if(_ButtonsIDController != nullptr)
	{
		if(IsActive())
			_ButtonsIDController->FreeButtonID(_id);

		std::shared_ptr<BaseButton> s_ptr(this);
		_id = _ButtonsIDController->GetFreeButtonID(s_ptr);
	}
}

void BaseButton::Define(const Coord &coord, const Size &size, const Colors::Color &color) const
{
	DefineButton(coord, size, _id, color);
}

void KolibriLib::PrintDebug(const UI::buttons::BaseButton &out)
{
	DebugOut("BaseButton: ID: ");
	PrintDebug(out.GetId());
	DebugOut("\n");
}