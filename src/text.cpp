#include <kolibriLib/UI/text/text.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

Char Txt::GetChar(int i) const
{
	assert(i < _data.size() && i >= 0);
    return _data.at(i);
}

std::string KolibriLib::UI::text::Txt::GetText() const
{
	std::string result;
	for (Char i : _data)
	{
		if (i.GetType() == Char::Type::Text)
		{
			result += i.GetChar();
		}
	}
	return result;
}

Txt::Txt()
{
	#ifdef Debug
	_ksys_debug_puts("Text constructor\n");
	#endif
}

Txt::Txt(const std::string &text)
{
	#ifdef Debug
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
	for (int i = 0; i < txt.length(); i++)
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
		_data.insert(_data.begin() + i, Char(txt[j]));
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
	#ifdef Debug
	_ksys_debug_puts("Print Txt:");
	#endif
	int buff = 0;
	for (Char i : _data)
	{
		#ifdef Debug
		char* b;
		b[0] = i.GetChar();
		b[1] = '\n';
		b[2] = '\0';
		_ksys_debug_puts(b);
		#endif

		i.Print(Coord(coord.x + buff, coord.y));
		buff += i.GetFont().size.x;
	}
	#ifdef Debug
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
	for (Char i : _data)
	{
		l += i.GetFont().size.x;
	}
	return l;
}

void KolibriLib::UI::text::Txt::SetText(const std::string& text)
{
	#ifdef Debug
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
		width += i.GetFont().size.x;
	}
	return width;
}