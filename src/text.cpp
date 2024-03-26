#include <kolibriLib/UI/text/text.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

const Char &Txt::GetChar(int i) const
{
    return _data.at(i);
}

std::string &KolibriLib::UI::text::Txt::GetText() const
{
	std::string result;
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].GetType() == Char::Type::Text)
		{
			result += _data[i].GetChar();
		}
	}
	return result;
}

Txt::Txt()
{
	_ksys_debug_puts("Text constructor\n");
}

Txt::Txt(const std::string &text)
{
#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
#endif

	SetText(text);
}

void KolibriLib::UI::text::Txt::Add(const KolibriLib::UI::text::Char &c)
{
	_data.push_back(c);
}

void KolibriLib::UI::text::Txt::Add(const std::string &txt)
{
	if (_data.size() == 0)
	{
		_data.push_back(Char(txt[0])); // На случай если вектор пустой
	}
	for (int i = 1; i < txt.length(); i++)
	{
		_data.push_back(Char(txt[i]));
	}
}

void KolibriLib::UI::text::Txt::Add(const Images::img &img)
{
	_data.push_back(Char(img));
}
void KolibriLib::UI::text::Txt::insert(const KolibriLib::UI::text::Char &c, int i)
{
	_data.insert(_data.begin() + i, c);
}

void KolibriLib::UI::text::Txt::insert(const std::string &txt, int i)
{
	for (int j = txt.length(); j > 0; j++)
	{
		_data.insert(_data.begin() + i, Char(txt[j], _data[i].GetFont()));
	}
}

void KolibriLib::UI::text::Txt::insert(const Images::img &img, int i)
{
	_data.insert(_data.begin() + i, Char(img));
}

void KolibriLib::UI::text::Txt::Delete(int i)
{
	_data.erase(_data.begin() + i);
}

void KolibriLib::UI::text::Txt::Print(const Coord &coord) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Print Txt:");
	#endif
	int buff = 0;
	for (int i = 0; i < _data.size(); i++)
	{
		_data[i].Print(Coord(coord.x + buff, coord.y));
		buff += _data[i].GetFont().size.x;
	}
	#ifdef DEBUG
	_ksys_debug_puts("done!\n");
	#endif
}

void KolibriLib::UI::text::Txt::SetFont(const Fonts::Font &Font)
{
	for (int i = 0; i < _data.size(); i++)
	{
		_data[i].SetFont(Font);
	}
}

void KolibriLib::UI::text::Txt::SetTextColor(const Colors::Color &Color)
{
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].GetType() == Char::Type::Text)
		{
			_data[i].SetTextColor(Color);
		}
	}
}

void KolibriLib::UI::text::Txt::SetBackgroundColor(const Colors::Color &Color)
{
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].GetType() == Char::Type::Text)
		{
			_data[i].SetBackgroundColor(Color);
		}
	}
}

bool KolibriLib::UI::text::Txt::operator==(const KolibriLib::UI::text::Txt &txt) const
{
	return _data == txt._data;
}

std::size_t KolibriLib::UI::text::Txt::length() const
{
	return _data.size();
}

unsigned KolibriLib::UI::text::Txt::lenghtPX() const
{
	unsigned l = 0;
	for (unsigned i = 0; i < _data.size(); i++)
	{
		l += _data[i].GetFont().size.x;
	}
	return l;
}

void KolibriLib::UI::text::Txt::SetText(std::string text)
{
	for (std::size_t i = 0; i < text.length(); i++)
	{
		_data[i].Set(text[i], _data[i].GetFont());
	}
}

KolibriLib::UI::text::Txt &KolibriLib::UI::text::Txt::operator=(const Txt &txt)
{
	_data = txt._data;
	return *this;
}