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
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif
	//_font = new Fonts::Font(Fonts::DefaultFont);
	_TextColor = new Colors::Color(OS::GetSystemColors().gui_text);
}

Txt::Txt(const std::string &text, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
	: _data(text), _TextColor(TextColor), _BackgroundColor(BackgroundColor)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif

	//_font = new Fonts::Font(Fonts::DefaultFont);
}

KolibriLib::UI::text::Txt::Txt(const Txt &copy)
	:_data(copy._data), _TextColor(copy._TextColor), _BackgroundColor(copy._BackgroundColor)
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

void KolibriLib::UI::text::Txt::Print(const Coord &coord) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Print Txt:");
	#endif

	if(_data.length() > 0)
	{
		/*uint8_t flags = 0;

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
		drawtext(coord, buff, _data, _CharSize, _TextColor, _BackgroundColor, flags);*/

		DrawText(_data, coord, _TextColor, TextEncoding::UTF8, _CharSize.x / 16);
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

void KolibriLib::UI::text::Txt::SetBackgroundColor(const Colors::Color &Color)
{
	_BackgroundColor = Color;
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

void KolibriLib::UI::text::Txt::SetTextSize(const Size &NewTextCharSize)
{
	_CharSize = NewTextCharSize;
}