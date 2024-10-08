#include <kolibriLib/UI/text/textlabel.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

TextLabel::TextLabel(const UDim &coord, const UDim &size, const std::string &text, const Size &CharSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin)
	:	Txt(text, TextColor),
		UIElement(coord, size, Globals::SystemColors.work_area, Margin)
{
	PrintDebug("TextLabel Constructor\n");

	_TextScale = TextScale;

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
	_Align = copy._Align;
	_TextScale = copy._TextScale;
}

void text::TextLabel::Render() const
{
	if(Visible)
	{

		Coord pos = GetAbsoluteCoord();
		Size size = GetAbsoluteSize();

		switch (_Align)
		{
		case TextLabel::Align::Center:

			pos.x += (size.x - static_cast<int>(lenghtPX())) / 2;
			pos.y += size.y / 2;

			break;
		case TextLabel::Align::Left:

			pos.y += size.y / 2;

			break;

		case TextLabel::Align::Right:

			pos.x += size.x - static_cast<int>(lenghtPX());
			pos.y += size.y / 2;

			break;
		default:
			_ksys_debug_puts("Unklown value of TextLabel::_Align");
		}

		Print(pos, _MainColor);
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

void KolibriLib::UI::text::TextLabel::SetAling(TextLabel::Align aling)
{
	_Align = aling;
}

TextLabel::Align KolibriLib::UI::text::TextLabel::GetAling() const
{
	return _Align;
}

bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
{
	return static_cast<UIElement>(*this) == static_cast<UIElement>(a) &&
	       static_cast<Txt>(*this) == static_cast<Txt>(a) &&
		   _Align == _Align &&
		   _TextScale == _TextScale;
}

bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
{
	return static_cast<UIElement>(*this) != static_cast<UIElement>(a) ||
	       static_cast<Txt>(*this) != static_cast<Txt>(a) ||
		   _Align != _Align ||
		   _TextScale != _TextScale;
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