#include <kolibriLib/UI/buttonsBase.hpp>
#include <algorithm>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;


/// @brief Список использованных id кнопок
std::vector<ButtonID> ButtonsIdList {/*CloseButton,*/ MinimizeButton};

ButtonID buttons::GetFreeButtonId()
{
	for(ButtonID i = 2; i < 0x8000; i++)	// в wiki сказанно что id в промежутке (0, 0x8000)
	{                                   	// CloseButton = 1, поэтому пропускаем и начинаем сразу с 2
		if(std::find(ButtonsIdList.begin(), ButtonsIdList.end(), i) == ButtonsIdList.end())
		{
			ButtonsIdList.push_back(i);
			return i;
		}
	}
	return 0;
}

void buttons::FreeButtonId(const ButtonID &id)
{
	auto a = std::find(ButtonsIdList.begin(), ButtonsIdList.end(), id);
	if(!(a == ButtonsIdList.end()))
	{
		ButtonsIdList.erase(a);
	}
}

ButtonID buttons::autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color)
{
	ButtonID id = GetFreeButtonId(); // Автоматически получаем id для кнопки
	DefineButton(coords, size, id, color);
	return id;
}