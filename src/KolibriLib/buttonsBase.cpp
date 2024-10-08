#include <kolibriLib/UI/buttons/buttonsBase.hpp>
#include <algorithm>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

UI::buttons::ButtonsIDController *Globals::DefaultButtonsIDController = nullptr;

ButtonID buttons::GetFreeButtonId(ButtonIDList *ButtonsIdList, uint32_t startID)
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

bool buttons::FreeButtonId(const ButtonID &id, ButtonIDList *ButtonsIdList)
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

ButtonID buttons::autoDefineButton(ButtonIDList *ButtonsIdList, const Coord &coords, const Size &size, const Colors::Color &color)
{
	ButtonID id = GetFreeButtonId(ButtonsIdList); // Автоматически получаем id для кнопки
	DefineButton(coords, size, id, color);
	return id;
}

/*
	ButtonsIDController
*/

ButtonID buttons::ButtonsIDController::GetFreeButtonID(std::shared_ptr<BaseButton> ptr)
{
	ButtonIDList buttonslist;
	buttonslist.reserve(ButtonsIdList.size());

	for(ButtonsIDController::node i : ButtonsIdList)
	{
		buttonslist.push_back(i.id);
	}

	ButtonID ret = GetFreeButtonId(&buttonslist, _top);

	if(ret == ButtonIDNotSet)	// Если неудалось найти свободный ID 
	{                        	// то начиаем с начала
		_top = StartTop;
		ret = GetFreeButtonId(&buttonslist, _top);	// попытка вторая
	}
		
	_top = ret.value + 1;


	ButtonsIDController::node n(buttonslist.back());

	if(ptr)
		n.pointer = ptr;

	ButtonsIdList.push_back(n);

	return ret;
}


void buttons::ButtonsIDController::FreeButtonID(const ButtonID &id)
{
	ButtonIDList buttonslist;
	buttonslist.reserve(ButtonsIdList.size());

	for(ButtonsIDController::node i : ButtonsIdList)
	{
		buttonslist.push_back(i.id);
	}

	if(FreeButtonId(id, &buttonslist) && id.value == _top-1)
	{
		_top--;
	}

	for(std::size_t i = 0; i < buttonslist.size(); i++)
	{
		ButtonsIdList[i] = ButtonsIDController::node(buttonslist[i], ButtonsIdList[i].pointer);
	}
}

ButtonsIDController::List& buttons::ButtonsIDController::GetButtonsIDList()
{
	return ButtonsIdList;
}

const ButtonsIDController::List& buttons::ButtonsIDController::GetButtonsIDList() const
{
	return ButtonsIdList;
}

std::shared_ptr<BaseButton> KolibriLib::UI::buttons::ButtonsIDController::GetPoinerToButton(const ButtonID &ID) const
{
	std::shared_ptr<BaseButton> ret;

	std::find_if(ButtonsIdList.begin(), ButtonsIdList.end(),
		[&ID, &ret](const ButtonsIDController::node& n){
			if(n.id == ID)
			{
				ret = n.pointer;
				return true;
			}
			return false;
		}
	);

	return ret;
}

/* 
	ButtonID 
*/

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

KolibriLib::UI::buttons::ButtonID::operator std::uint32_t() const
{
	return value;
}

bool KolibriLib::UI::buttons::ButtonID::operator==(const ButtonID &val) const
{
	return value == val.value;
}

bool KolibriLib::UI::buttons::ButtonID::operator!=(const ButtonID &val) const
{
	return value != val.value;
}

void KolibriLib::UI::buttons::ButtonID::swap(ButtonID &val)
{
	std::uint32_t buff = value;

	value = val.value;
	val.value = buff;
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
