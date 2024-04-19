#include <kolibriLib/UI/text/char.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;


KolibriLib::UI::text::Char::Char(char c, const Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
	: _c(c), _font(new Fonts::Font(font)), _TextColor(new Colors::Color(TextColor)), _BackgroundColor(new Colors::Color(BackgroundColor))
{
	
}

KolibriLib::UI::text::Char::Char(const Char &copy) 
	: _font(copy._font), _c(copy._c)
{
	#ifdef DEBUG
	_ksys_debug_puts("Char constructor(copy)\n");
	#endif

}

KolibriLib::UI::text::Char::~Char()
{
	
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

void KolibriLib::UI::text::Char::SetFont(const KolibriLib::UI::text::Fonts::Font &newFont) const
{
	

}

const Fonts::Font KolibriLib::UI::text::Char::GetFont() const
{
	
}

unsigned KolibriLib::UI::text::Char::GetFlags() const
{
	
}


void KolibriLib::UI::text::Char::Print(const Coord &coord) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Print Char\n");
	#endif

	FT_Error error = FT_Load_Char(_font->_face, _c, FT_LOAD_RENDER);
	DrawGlyphSlot(_font->_face->glyph, coord);
}

KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(char c)
{
	
}



KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(const KolibriLib::UI::text::Char &c)
{
	
}

bool Char::operator==(const Char &img) const
{
	return (_font == img._font);
}


bool KolibriLib::UI::text::Char::operator==(char c) const
{
	
}

bool KolibriLib::UI::text::Char::operator!=(char c) const
{
	
}
