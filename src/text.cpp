#include <kolibriLib/UI/text/text.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

Char Txt::GetChar(int i) const
{
    return _data.at(i);
}

std::string KolibriLib::UI::text::Txt::GetText() const
{
	std::string result;
	for (Char i : _data)
	{
		result += i.GetChar();
	}
	return result;
}

Txt::Txt()
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif
}

Txt::Txt(const std::string &text)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif

	SetText(text);
}

KolibriLib::UI::text::Txt::Txt(const Txt & copy)
	:_data(copy._data)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor(copy)\n");
	#endif
}

void KolibriLib::UI::text::Txt::Add(const KolibriLib::UI::text::Char &c)
{
	_data.push_back(c);
}

void KolibriLib::UI::text::Txt::Add(const std::string &txt)
{
	for (int i = 0; i < txt.length(); i++)
	{
		_data.push_back(Char(txt[i]));
	}
}

void KolibriLib::UI::text::Txt::insert(const KolibriLib::UI::text::Char &c, int i)
{
	_data.insert(_data.begin() + i, c);
}

void KolibriLib::UI::text::Txt::insert(const std::string &txt, int i)
{
	for (int j = txt.length(); j > 0; j++)
	{
		_data.insert(_data.begin() + i, Char(txt[j]));
	}
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
	for (const Char i : _data)
	{
		i.Print({coord.x + buff, coord.y});
		buff += 16;
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
		_data[i].SetTextColor(Color);
	}
}

void KolibriLib::UI::text::Txt::SetBackgroundColor(const Colors::Color &Color)
{
	for (int i = 0; i < _data.size(); i++)
	{
		_data[i].SetBackgroundColor(Color);
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
	for (Char i : _data)
	{
		l += 16;
	}
	return l;
}

void KolibriLib::UI::text::Txt::SetText(const std::string& text)
{
	#ifdef DEBUG
	_ksys_debug_puts("Set Text to:");
	_ksys_debug_puts(text.c_str());
	_ksys_debug_puts("\n");
	#endif
	
	_data.reserve(text.length());

	
	for (std::size_t i = 0; i < text.length(); i++)
	{
		_data.push_back(Char(text.at(i)));
	}
	
}

KolibriLib::UI::text::Txt &KolibriLib::UI::text::Txt::operator=(const Txt &txt)
{
	_data = txt._data;
	return *this;
}

unsigned KolibriLib::UI::text::Txt::GetWidth() const
{
	unsigned width = 0;
	for( Char i : _data)
	{
		width += 16;
	}
	return width;
}

