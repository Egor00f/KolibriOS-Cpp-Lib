#include <kolibriLib/UI/text/fonts.hpp>

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
	: _Font(FontFamily), _Flags(flags)
{
	#ifdef Debug
	_ksys_debug_puts("Font constructor\n");
	#endif
	SetFontSize((unsigned)FontSize);
}

void KolibriLib::UI::text::Fonts::Font::SetFontSize(unsigned FontSize)
{
	_FontSize = FontSize;
	size = _Font;
	
	float buff = static_cast<float>(FontSize) / static_cast<float>(_Font.y);
	
	size *= static_cast<int>(buff);
}