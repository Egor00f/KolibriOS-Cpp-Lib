#include <kolibriLib/UI/text/text.hpp>
#include <C_Layer/INCLUDE/kolibri_rasterworks.h>

using namespace KolibriLib;
using namespace UI;
using namespace text;


/*
	Contructors
*/

Txt::Txt(const std::string &text, const Colors::Color &TextColor)
	:	_data	(text),
		_TextColor	(TextColor)
{
	#ifdef DEBUG
	_ksys_debug_puts("Text constructor\n");
	#endif

	//_font = new Fonts::Font(Fonts::DefaultFont);
}

/*
	Funcs
*/

std::string KolibriLib::UI::text::Txt::GetText() const
{
	return _data;
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

void KolibriLib::UI::text::Txt::Print(Coord pos, Size size, const Colors::Color &BackgroundColor) const
{
	PrintDebug("Print Txt\n");

	/*if(_data.length() > 0)	// Если текста не то и выводить нечего
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

		drawtext(coord, buff, _data, _CharSize, _TextColor, BackgroundColor, flags);
	}*/

	switch (_Align)
	{
	case Txt::Align::Center:

		pos.x += (size.x - static_cast<int>(lenghtPX())) / 2;
		pos.y += size.y / 2;

		break;
	case Txt::Align::Left:

		pos.y += size.y / 2;

		break;

	case Txt::Align::Right:

		pos.x += size.x - static_cast<int>(lenghtPX());
		pos.y += size.y / 2;

		break;
	default:
		_ksys_debug_puts("Unklown value of Txt::_Align");
	}

	DrawText(_data, pos, _TextColor, TextEncoding::UTF8, _CharSize.x / 16);
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

void text::Txt::SetScale(bool scale)
{
	_TextScale = scale;
}

bool Txt::GetScale() const
{
	return _TextScale;
}

void KolibriLib::UI::text::Txt::SetAling(Txt::Align aling)
{
	_Align = aling;
}

Txt::Align KolibriLib::UI::text::Txt::GetAling() const
{
	return _Align;
}

/*
	Operators
*/

bool KolibriLib::UI::text::Txt::operator==(const KolibriLib::UI::text::Txt &txt) const
{
	return _data == txt._data &&
	       _TextColor == txt._TextColor;
}

bool KolibriLib::UI::text::Txt::operator!=(const Txt &txt) const
{
	return _data != txt._data ||
	       _TextColor != txt._TextColor;
}


void KolibriLib::PrintDebug(const UI::text::Txt &out)
{
	DebugOut("Txt:\n");
	PrintDebug(out.GetText());
	DebugOut("\n");
	PrintDebug(out.GetTextColor());
	DebugOut("\n");
}