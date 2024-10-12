#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const Size &CharSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin)
	:	Txt(text, TextColor),
		UIElement(coord, size, Globals::SystemColors.work_area, Margin)
{
	PrintDebug("TextLabel Constructor\n");


	SetTextSize(CharSize);
	//SetFont(Fonts::Font(Fonts::DefaultFont.font_file, FontSize));
}

KolibriLib::UI::text::TextLabel::TextLabel(const UDim &coord, const UDim &size, const Txt &text)
	:	Txt(text),
		UIElement(coord, size, Globals::SystemColors.work_area)
{
	PrintDebug("TextLabel Constructor\n");
}

TextLabel::TextLabel(const TextLabel &copy)
	:	Txt	(copy),
		UIElement	(copy)
{
}

void text::TextLabel::Render() const
{
	if(Visible)
		Print(GetAbsoluteCoord(), GetAbsoluteSize(), _MainColor);
}



bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
{
	return static_cast<UIElement>(*this) == static_cast<UIElement>(a) &&
	       static_cast<Txt>(*this) == static_cast<Txt>(a);
}

bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
{
	return static_cast<UIElement>(*this) != static_cast<UIElement>(a) ||
	       static_cast<Txt>(*this) != static_cast<Txt>(a);
}

void KolibriLib::UI::text::TextLabel::swap(TextLabel &a)
{
	TextLabel buff(*this);

	*this = a;
	a = buff;
}

void KolibriLib::PrintDebug(const UI::text::TextLabel &out)
{
	PrintDebug(static_cast <UIElement>(out));
	PrintDebug(static_cast<Txt>(out));
}