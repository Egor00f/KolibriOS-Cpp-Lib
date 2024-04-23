#include <kolibriLib/UI/text/char.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;


KolibriLib::UI::text::Char::Char(char c, const Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
	: _c(c), _font(new Fonts::Font(font)), _TextColor(new Colors::Color(TextColor)), _BackgroundColor(new Colors::Color(BackgroundColor)),
	  ExternBackgroundColor(false), ExternFont(false), ExternTextColor(false)
{
	
}

KolibriLib::UI::text::Char::Char(const Char &copy)
	: _c(copy._c), ExternBackgroundColor(copy.ExternBackgroundColor), ExternFont(copy._font), ExternTextColor(copy.ExternTextColor)
{
	if (copy.ExternBackgroundColor)
		_BackgroundColor = copy._BackgroundColor;
	else
		_BackgroundColor = new Colors::Color(copy._BackgroundColor);

	if (copy.ExternFont)
		_font = copy._font;
	else
		_font = new Fonts::Font(copy._font);

	if (copy.ExternTextColor)
		_TextColor = copy._TextColor;
	else
		_TextColor = new Colors::Color(copy._TextColor);

}

KolibriLib::UI::text::Char::~Char()
{
	if (!ExternFont)
		delete _font;
	if (!ExternTextColor)
		delete _TextColor;
	if (!ExternBackgroundColor)
		delete _BackgroundColor;
}

void KolibriLib::UI::text::Char::SetFlags(unsigned flags)
{
	
}

void KolibriLib::UI::text::Char::SetTextColor(const Colors::Color &NewColor)
{
	*this->_TextColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetBackgroundColor(const Colors::Color &NewColor)
{
	*this->_BackgroundColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetFont(const KolibriLib::UI::text::Fonts::Font &newFont)
{
	if(!ExternFont)
	{
		delete _font;
	}
	_font = new Fonts::Font(newFont);
}

const Fonts::Font KolibriLib::UI::text::Char::GetFont() const
{
	return *_font;
}


void KolibriLib::UI::text::Char::Print(const Coord &coord) const
{
	char *b = new char[2];
	b[0] = _c;
	b[1] = '\0';
	FreeType::FT_Error error = FreeType::DrawText(b, _font->_face, coord);
	delete[] b;
	if(error != 0)
	{
		_ksys_debug_puts("Error Load Char\n");
	}
}

KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(char c)
{
	_c = c;

	return *this;
}

char KolibriLib::UI::text::Char::GetChar() const
{
	return _c;
}

KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(const KolibriLib::UI::text::Char &c)
{
	_c = c._c;
	_font = new Fonts::Font(c._font);
	_TextColor = new Colors::Color(c._TextColor);
	_BackgroundColor = new Colors::Color(c._BackgroundColor);
	return *this;
}

bool Char::operator==(const Char &img) const
{
	return (_font == img._font);
}


bool KolibriLib::UI::text::Char::operator==(char c) const
{
	return _c == c;
}

bool KolibriLib::UI::text::Char::operator!=(char c) const
{
	return _c != c;
}