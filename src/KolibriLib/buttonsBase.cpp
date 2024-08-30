#include <kolibriLib/UI/buttons/buttonsBase.hpp>
#include <algorithm>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

UI::buttons::ButtonsIDController *Globals::DefaultButtonsIDController;

ButtonID buttons::GetFreeButtonId(std::vector<ButtonID> *ButtonsIdList, uint32_t startID)
{
	for(ButtonID i = startID; i < buttons::ButtonIDEnd; i.value++)	// в wiki сказанно что id в промежутке (0, 0x8000)
	{                                   	// CloseButton = 1, поэтому пропускаем и начинаем сразу с 2
		if(std::find(ButtonsIdList->begin(), ButtonsIdList->end(), i) == ButtonsIdList->end())
		{
			ButtonsIdList->push_back(i);
			return i;
		}
	}
	
	return ButtonIDNotSet;
}

bool buttons::FreeButtonId(const ButtonID &id, std::vector<ButtonID> *ButtonsIdList)
{
	auto a = std::find(ButtonsIdList->begin(), ButtonsIdList->end(), id);
	if(!(a == ButtonsIdList->end()))
	{
		ButtonsIdList->erase(a);
		return true;
	}
	else
	{
		return false;
	}
}

ButtonID buttons::autoDefineButton(std::vector<ButtonID>*ButtonsIdList, const Coord &coords, const Size &size, const Colors::Color &color)
{
	ButtonID id = GetFreeButtonId(ButtonsIdList); // Автоматически получаем id для кнопки
	DefineButton(coords, size, id, color);
	return id;
}

ButtonID buttons::ButtonsIDController::GetFreeButtonID()
{
	ButtonID ret = GetFreeButtonId(&ButtonsIdList, _top);

	if(ret == ButtonIDNotSet)
	{
		_top = 2;
		ret = GetFreeButtonId(&ButtonsIdList, _top);
	}
	else
	{
		_top = ret.value + 1;
	}

	return ret;
}


void buttons::ButtonsIDController::FreeButtonID(const ButtonID &id)
{
	if(id.value == _top-1 && FreeButtonId(id, &ButtonsIdList))
	{
		_top--;
	}
}

std::vector<ButtonID>* buttons::ButtonsIDController::GetButtonsIDList()
{
	return &ButtonsIdList;
}

const std::vector<ButtonID>* buttons::ButtonsIDController::GetButtonsIDList() const
{
	return &ButtonsIdList;
}

void KolibriLib::PrintDebug(UI::buttons::ButtonID out)
{
	if(out.CheckIsValid())
	{
		PrintDebug(static_cast<unsigned>(out));
	}
	else
	{
		if (out.value == ButtonIDNotSet)
		{
			DebugOut("Not set");
		}
		else if (out.value >= ButtonIDEnd)
		{
			DebugOut("Out of acceptable values");
		}
		else
		{
			DebugOut("ID not valid, but != 0 and < 0x8000, WTF?");
		}
	}
}

KolibriLib::UI::buttons::ButtonID::ButtonID(unsigned val)
	:	value(val)
{
}

bool KolibriLib::UI::buttons::ButtonID::CheckIsValid() const
{
	return value != ButtonIDNotSet.value && value < ButtonIDEnd.value;
}

ButtonID KolibriLib::UI::buttons::ButtonID::operator=(const unsigned &val)
{
	return ButtonID(val);
}

KolibriLib::UI::buttons::ButtonID::operator uint32_t() const
{
	return value;
}

