#include <kolibriLib/UI/menu.hpp>

using namespace KolibriLib;
using namespace UI;

Menu::Menu(const Coord &coord, const Size &size, const std::vector<std::string> &li, const unsigned &Margin, const Colors::Color &color) : UIElement(coord, size, color, Margin)
{
	for (int i = 0; i < li.size(); i++)
	{
		buttons::Button btn(Coord(coord.x, coord.y + ((size.y / li.size()) * i)), Size(size.x, size.y / li.size()), Margin, color);
		btn.insert(li[i], 0);
		_Buttons.push_back(btn);
	}
}

Menu::~Menu()
{
}
void Menu::Render()
{
	for (int i = 0; i < _Buttons.size(); i++)
	{
		_Buttons[i].Render();
	}
}

int KolibriLib::UI::Menu::Handler()
{
	for (int i = 0; i < _Buttons.size(); i++)
	{
		if (_Buttons[i].Handler())
		{
			return i;
		}
	}
	return -1;
}

int KolibriLib::UI::Menu::AddItem(const std::string &item, int i)
{
	buttons::Button btn({_coord.x, _coord.y + ((int)(_size.y / _Buttons.size()) * i)}, {_size.x}, _Margin, _MainColor);
	btn.insert(item, 0);
	if (i == -1)
	{
		_Buttons.push_back(btn);
		return _Buttons.size() - 1;
	}

	_Buttons.insert(_Buttons.begin() + i, btn);
	return 0;
}

void Menu::SetItem(const std::string &NewText, int i)
{
	_Buttons[i].SetText(NewText);
}

bool KolibriLib::UI::Menu::DeleteItem(unsigned i)
{
	if (_Buttons.size() <= i || i < 0)
	{
		return false;
	}

	_Buttons.erase(_Buttons.begin() + i);

	return true;
}