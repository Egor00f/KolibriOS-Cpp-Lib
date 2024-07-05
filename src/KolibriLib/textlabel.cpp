#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const Size &CharSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin)
	: Txt(text), 
		UIElement(coord, size, TextColor, Margin),
		_TextScale(TextScale)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif
	SetTextSize(CharSize);
	//SetFont(Fonts::Font(Fonts::DefaultFont.font_file, FontSize));
}


//TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, /*const UI::text::Fonts::Font &Font,*/ const Colors::Color &TextColor, const Colors::Color &BackgroundColor, bool TextScale, unsigned Margin)
//	: UIElement(coord, size, TextColor, Margin), Txt(text), _TextScale(TextScale)
//{
//	#ifdef DEBUG
//	_ksys_debug_puts("TextLabel Constructor\n");
//	#endif
	
	//SetFont(Font);
//}


KolibriLib::UI::text::TextLabel::TextLabel(const UDim &coord, const UDim &size, const Txt &text)
	:	Txt(text), 
		UIElement(coord, size)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif
}

TextLabel::TextLabel(const TextLabel &copy)
	:	Txt(copy), 
		UIElement(copy._coord, copy._size, copy._MainColor, copy._Margin), 
		_TextScale(copy._TextScale), 
		Align(copy.Align)
{
}

void text::TextLabel::Render() const
{

	Coord pos = _coord.GetAbsolute();
	Size size = _size.GetAbsolute();

	pos.x += (size.x - lenghtPX()) / 2;
	pos.y += size.y / 2;

	Print(pos);

	/*if(_TextScale)
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
			//Fonts::Font p = q.GetFont();

			//p._size = p._size + size;

			//q.SetFont(p);
		}

	}
	else
	{
		Print(_coord.GetAbsolute());
	}*/
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