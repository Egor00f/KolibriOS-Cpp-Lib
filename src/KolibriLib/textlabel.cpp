#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const Size &CharSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin)
	:	Txt(text, TextColor),
		UIElement(coord, size, OS::GetSystemColors().work_area, Margin),
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
		UIElement(coord, size, OS::GetSystemColors().work_area)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif
}

TextLabel::TextLabel(const TextLabel &copy)
	:	Txt	(copy._data, copy.GetTextColor()),
		UIElement	(copy._coord, copy._size, copy._MainColor, copy.GetMargin()),
		_TextScale	(copy._TextScale),
		_Align	(copy._Align)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor(copy)\n");
	#endif
}

void text::TextLabel::Render() const
{
	#ifdef DEBUG
	_ksys_debug_puts("Render TextLabel");
	#endif

	Coord pos = GetAbsoluteCoord();
	Size size = GetAbsoluteSize();

	switch (_Align)
	{
		case TextLabel::Aling::Center:

			pos.x += (size.x - lenghtPX()) / 2;
			pos.y += size.y / 2;

			break;
		case TextLabel::Aling::Left:

			pos.y += size.y / 2;

			break;

		case TextLabel::Aling::Right:

			pos.x += size.x - lenghtPX();
			pos.y += size.y / 2;

			break;
		default:
			_ksys_debug_puts("Unklown value of TextLabel::_Align");
	}

	Print(pos, _MainColor);
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
	SetMargin(a.GetMargin());
	_TextScale	= a._TextScale;
	return *this;
}

bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
{
	return	(_coord	==	a._coord)	&&
	        (_size	==	a._size)	&&
	        (_MainColor	==	a._MainColor)	&&
	        (GetMargin()	==	a.GetMargin())	&&
	        (_TextScale	==	a._TextScale);
}

bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
{
	return !((_coord	==	a._coord)	||
		   (_size	==	a._size)	||
		   (_MainColor	==	a._MainColor)	||
		   (GetMargin()	==	a.GetMargin())	||
		   (_TextScale	==	a._TextScale));
}

void KolibriLib::PrintDebug(const UI::text::TextLabel &out)
{
	PrintDebug((UIElement)out);
	PrintDebug((Txt)out);
}