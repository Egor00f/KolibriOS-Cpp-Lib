#include <kolibriLib/UI/text/text.hpp>
#include <C_Layer/INCLUDE/kolibri_rasterworks.h>

using namespace KolibriLib;
using namespace UI;
using namespace text;


std::string KolibriLib::UI::text::Txt::GetText() const
{
	return _data;
}

Txt::Txt()
	:	_CharSize	(DefaultCharSize),
		_TextColor	(OS::GetSystemColors().work_text),
		Italic	(false),
		Bold	(false),
		UnderLine	(false),
		StrikeThrough	(false)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif
	//_font = new Fonts::Font(Fonts::DefaultFont);
	

}

Txt::Txt(const std::string &text, const Colors::Color &TextColor)
	:	_data	(text),
		_TextColor	(TextColor),
		_CharSize	(DefaultCharSize),
		Italic	(false),
		Bold	(false),
		UnderLine	(false),
		StrikeThrough	(false)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif

	//_font = new Fonts::Font(Fonts::DefaultFont);
}

KolibriLib::UI::text::Txt::Txt(const Txt &copy)
	:	_data(copy._data),
		_TextColor(copy._TextColor),
		_CharSize(copy._CharSize),
		Italic(copy.Italic),
		Bold(copy.Bold),
		UnderLine(copy.UnderLine),
		StrikeThrough(copy.StrikeThrough)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor(copy)\n");
	#endif
}

void KolibriLib::UI::text::Txt::Add(const std::string &txt)
{
	_data += txt;
}

void KolibriLib::UI::text::Txt::insert(const std::string &txt, int i)
{
	_data.insert(i, txt);
}

void KolibriLib::UI::text::Txt::Delete(int i)
{
	_data.erase(_data.begin() + i);
}

void KolibriLib::UI::text::Txt::Print(const Coord &coord, const Colors::Color &BackgroundColor) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Print Txt:");
	#endif

	if(_data.length() > 0)	// Если текста не то и выводить нечего
	{
		uint8_t flags = 0;

		if (Italic)
			flags |= RasterworksParams::Italic;
		if (Bold)
			flags |= RasterworksParams::Bold;
		if (UnderLine)
			flags |= RasterworksParams::Underline;
		if (StrikeThrough)
			flags |= RasterworksParams::StrikeThrough;


		Size buff = _CharSize;
		buff.x *= _data.length();

		drawtext(coord, buff, _data, _CharSize, _TextColor, BackgroundColor, flags);
	}

	#ifdef DEBUG
	_ksys_debug_puts("done!\n");
	#endif
}

/*void KolibriLib::UI::text::Txt::SetFont(const Fonts::Font &Font)
{
	*_font = Font;
	for (Char i : _data)
	{
		i.SetFont(_font);
	}
}*/

void KolibriLib::UI::text::Txt::SetTextColor(const Colors::Color &Color)
{
	_TextColor = Color;
}



Colors::Color KolibriLib::UI::text::Txt::GetTextColor() const
{
	return _TextColor;
}


bool KolibriLib::UI::text::Txt::operator==(const KolibriLib::UI::text::Txt &txt) const
{
	return _data == txt._data;
}

std::size_t KolibriLib::UI::text::Txt::length() const
{
	return _data.length();
}

unsigned KolibriLib::UI::text::Txt::lenghtPX() const
{
	return _data.length() * _CharSize.x;
}

void KolibriLib::UI::text::Txt::SetText(const std::string& text)
{	
	_data = text;
	
}

KolibriLib::UI::text::Txt &KolibriLib::UI::text::Txt::operator=(const Txt &txt)
{
	_data = txt._data;
	return *this;
}

Size KolibriLib::UI::text::Txt::GetTextSize() const
{
	return _CharSize;
}

void KolibriLib::UI::text::Txt::SetTextSize(const Size &NewTextCharSize)
{
	_CharSize = NewTextCharSize;
}

char KolibriLib::UI::text::Txt::GetChar(std::size_t i) const
{
	return _data.at(i);
}

void KolibriLib::PrintDebug(const UI::text::Txt &out)
{
	DebugOut("Txt:\n");
	PrintDebug(out.GetText());
	DebugOut("\n");
	PrintDebug(out.GetTextColor());
	DebugOut("\n");
}