#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) 
	: UIElement(coord, size, TextColor, Margin), Txt(text), _TextScale(TextScale)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif

	SetFont(Fonts::Font(Fonts::DefaultFont.font_file, FontSize));
}

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const UI::text::Fonts::Font &Font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, bool TextScale, unsigned Margin)
	: UIElement(coord, size, TextColor, Margin), Txt(text), _TextScale(TextScale)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif
	
	SetFont(Font);
}

KolibriLib::UI::text::TextLabel::TextLabel(const UDim &coord, const UDim &size, const Txt &text)
	: UIElement(coord, size), Txt(text)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif
}

TextLabel::TextLabel(const TextLabel &copy)
	: UIElement(copy), _TextScale(copy._TextScale)
{
	_data = copy._data;
	_font = new Fonts::Font(*copy._font);
	_TextColor = new Colors::Color(*copy._TextColor);
}

void text::TextLabel::Render() const
{
	#ifdef DEBUG
	_ksys_debug_puts("Render textLabel:\n");
	#endif
	if(_TextScale)
	{
		Size size = {0,0};
		for(Char i :_data)
		{
			if(i.GetFont()._size > size)
			{
				size > i.GetFont()._size;
			}
		}

		size  = _size.GetAbsolute() - Size(size.x * length(), size.y * length());

		Txt t(*this);

		for(std::size_t i = 0; i < t.length(); i++)
		{
			Char q = t.GetChar(i);
			Fonts::Font p = q.GetFont();

			p._size = p._size + size;

			q.SetFont(p);
		}

	}
	else
	{
		Print(_coord);
	}
}

void text::TextLabel::SetScale(bool scale)
{
	_TextScale = scale;
}

bool TextLabel::GetScale() const
{
	return _TextScale;
}

text::TextLabel &KolibriLib::UI::text::TextLabel::operator=(const KolibriLib::UI::text::TextLabel &a)
{
	_coord	= a._coord;
	_size	= a._size;
	_MainColor	= a._MainColor;
	_Margin	= a._Margin;
	_TextScale	= a._TextScale;
	return *this;
}

bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
{
	return (_coord	==	a._coord)	&&
		   (_size	==	a._size)	&&
		   (_MainColor	==	a._MainColor)	&&
		   (_Margin	==	a._Margin)	&&
		   (_TextScale	==	a._TextScale);
}

bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
{
	return (_coord	==	a._coord)	||
		   (_size	==	a._size)	||
		   (_MainColor	==	a._MainColor)	||
		   (_Margin	==	a._Margin)	||
		   (_TextScale	==	a._TextScale);
}