#include <kolibriLib/UI/buttonsBase.hpp>
#include <unordered_map>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;

/// @brief Список idшников кнопок
std::unordered_map<ButtonID, bool> ButtonsIdList;

ButtonID buttons::GetFreeButtonId()
{
	for (unsigned i = 0; i < ButtonsIdList.size(); i++)
	{
		if (ButtonsIdList.count(i) == 0)
		{
			ButtonID ret = i + StartButtonId;
			if (ret == MinimizeButton)
				ret++;
			return ret;
		}
	}
}

void buttons::FreeButtonId(const ButtonID &id)
{
	ButtonsIdList.erase(id);
}

ButtonID buttons::autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color)
{
	ButtonID id = GetFreeButtonId(); // Автоматически получаем id для кнопки
	DefineButton(coords, size, id, color);
	return id;
}