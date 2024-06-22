#include <kolibriLib/UI/menu.hpp>

#include <kolibriLib/graphic/graphic.hpp>


using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::Menu::Item::Item(const text::Txt &text, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, Menu *underMenu)
	: buttons::Button(text)
{
	SetTextColor(TextColor);
	SetBackgroundColor(BackgroundColor);
	_undermenu = underMenu;
}

KolibriLib::UI::Menu::Item::Item(const Item &copy)
	: buttons::Button(copy)
{
	_undermenu = copy._undermenu;
}

KolibriLib::UI::Menu::Item::~Item()
{

}

Menu::Menu(const UDim &coord, const UDim &size, const std::vector<std::string> &li, const unsigned &Margin, const Colors::Color &color)
	: UIElement(coord, size, color, Margin)
{
	for (int i = 0; i < li.size(); i++)
	{
		_Buttons.push_back(new Menu::Item(buttons::Button(
			li[i],
			UDim(coord.X.Scale,
				 coord.X.Offset,
				 coord.Y.Scale * i,
				 coord.Y.Offset * i),
			UDim(size),
			Margin,
			color)));
	}

}

KolibriLib::UI::Menu::Menu(const Menu &copy)
	: UIElement(copy), _Buttons(copy._Buttons)
{
}

KolibriLib::UI::Menu::Item::Item(const buttons::Button &copy)
	: buttons::Button(copy)
{
}



void Menu::Render()
{
	for (auto i : _Buttons)
	{
		i.get()->Render();
	}
}

int KolibriLib::UI::Menu::Handler()
{
	for (std::size_t i = 0; i < _Buttons.size(); i++)
	{
		if (_Buttons[i].get()->Handler())
		{
			return i;
		}
	}
	return -1;
}

int KolibriLib::UI::Menu::AddItem(const std::string &item, int i)
{
	buttons::Button btn(UDim(
			_coord.X.Scale,
			_coord.X.Offset,
			_size.Y.Scale * i,
			_size.Y.Offset * i
		), 
		_size, 
		_Margin,
		_MainColor
	);
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