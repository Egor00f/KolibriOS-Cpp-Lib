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
		_id = KolibriLib::Globals::DefaultButtonsIDController->GetFreeButtonID();
	}
}

BaseButton::BaseButton(ButtonID id)
	:	_id(id)
{
	if (KolibriLib::Globals::DefaultButtonsIDController != nullptr)
	{
		_ButtonsIDController = KolibriLib::Globals::DefaultButtonsIDController;
	}
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
}

void BaseButton::BaseButton::Activate()
{
	if (!IsActive())
	{
		_id	= _ButtonsIDController->GetFreeButtonID();
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
	_id	= NewID;
}

void KolibriLib::UI::buttons::BaseButton::SetId()
{
	Deactivate();
	Activate();
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