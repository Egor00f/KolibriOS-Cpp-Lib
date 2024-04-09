#include <kolibriLib/UI/menu.hpp>

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::Menu::Item::Item(const text::Txt &text, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, Menu *underMenu)
	: buttons::Button(text, NULL, NULL, NULL, BackgroundColor)
{
	_undermenu = underMenu;
}

KolibriLib::UI::Menu::Item::Item(const Item &copy)
	: buttons::Button(copy)
{
	_undermenu = copy._undermenu;
}

Menu::Menu(const Coord &coord, const Size &size, const std::vector<Menu::Item> &li, const unsigned &Margin, const Colors::Color &color) 
	: UIElement(coord, size, color, Margin)
{
	for (int i = 0; i < li.size(); i++)
	{
		_Buttons.push_back(Menu::Item(buttons::Button(li[i], Coord(coord.x, coord.y + ((size.y / li.size()) * i)), Size(size.x, size.y / li.size()), Margin, color)));
	}

}

KolibriLib::UI::Menu::Menu(const Menu &copy)
	: UIElement(copy), _Buttons(copy._Buttons)
{
}

Menu::~Menu()
{
}

void Menu::Render()
{
	for (Menu::Item i : _Buttons)
	{
		i.Render();
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
	btn.Add(item);

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

	_Buttons.erase(_Buttons.begin() + i);

	return true;
}