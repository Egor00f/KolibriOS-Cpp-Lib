#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) : UIElement(coord, size, TextColor, Margin), Txt(text)
{
	#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
	#endif

	Fonts::Font f(Fonts::DefaultFont);
	f.SetFontSize(FontSize);
	SetFont(f);
	f.~Font();

	_TextScale = TextScale;
}

TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const UI::text::Fonts::Font &Font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, bool TextScale, unsigned Margin) : UIElement(coord, size, TextColor, Margin), Txt(text)
{
#ifdef DEBUG
	_ksys_debug_puts("TextLabel Constructor\n");
#endif
	_TextScale = TextScale;
	SetFont(Font);
}

void text::TextLabel::Render() const
{
	#ifdef DEBUG
	_ksys_debug_puts("Render textLabel:");
	#endif

	//  unsigned *FontSize = new unsigned;
	// *FontSize = 0;
	// if (_TextScale) // Если текст нужно подстраивать размер, то
	//{               // Постраиваем
	//    #ifdef DEBUG
	//    _ksys_debug_puts("ScaleText:");
	//    #endif
	// Программа сдесь крашится
	// Пока без этого
	// *FontSize = _size.x / lenghtPX();
	// if (!_Aligned)
	// {
	//     for (int i = 0; i < _data.size(); i++)
	//     {
	//         Fonts::Font buff = _data[i].GetFont();
	//         _data[i].SetFont(Fonts::Font(buff._Font, *FontSize, buff._Flags));
	//     }
	//     _Aligned = true;
	// }
	//    #ifdef DEBUG
	//    _ksys_debug_puts("done\n");
	//    #endif
	// }
	// delete FontSize;
	Print(Coord(_coord.x + (_size.x / 2), _coord.y + (_size.y / 2)));
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
	_coord = a._coord;
	_size = a._size;
	_MainColor = a._MainColor;
	_Margin = a._Margin;
	_TextScale = a._TextScale;
	return *this;
}

bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
{
	return (_coord == a._coord) &&
		   (_size == a._size) &&
		   (_MainColor == a._MainColor) &&
		   (_Margin == a._Margin) &&
		   (_TextScale == a._TextScale);
}

bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
{
	return (_coord == a._coord) ||
		   (_size == a._size) ||
		   (_MainColor == a._MainColor) ||
		   (_Margin == a._Margin) ||
		   (_TextScale == a._TextScale);
}