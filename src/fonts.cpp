#include <kolibriLib/UI/fonts.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font &KolibriLib::UI::text::Fonts::Font::operator=(const KolibriLib::UI::text::Fonts::Font &f)
{
	_Font = f._Font;
	_FontSize = f._FontSize;
	_Flags = f._Flags;
	return *this;
}

bool KolibriLib::UI::text::Fonts::Font::operator==(const KolibriLib::UI::text::Fonts::Font &f) const
{
	return (_Font == f._Font) &&
		   (_FontSize == f._FontSize) &&
		   (_Flags == f._Flags);
}

KolibriLib::UI::text::Fonts::Font::Font(const Size &FontFamily, int FontSize, unsigned flags)
{
	_ksys_debug_puts("Font constructor\n");
	_Font = FontFamily;
	_Flags = flags;
	SetFontSize((unsigned)FontSize);
}

void KolibriLib::UI::text::Fonts::Font::SetFontSize(unsigned FontSize)
{
	_ksys_debug_puts("Font setfotnsize\n");
	float buff = FontSize / _Font.x;
	_FontSize = FontSize;
	size = _Font;
	size /= buff;
}