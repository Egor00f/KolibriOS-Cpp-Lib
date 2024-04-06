#include <kolibriLib/UI/buttonsBase.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace buttons;



ButtonID autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color)
{
	ButtonID id = GetFreeButtonId(); // Автоматически получаем id для кнопки
	_ksys_define_button(coords.x, coords.y, size.x, size.y, id, color.val);
	return id;
}