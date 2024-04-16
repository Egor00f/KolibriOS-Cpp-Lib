#include <kolibriLib/UI/text/textBase.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;


Images::img KolibriLib::UI::text::DrawTextToImg(const std::string &text, const Fonts::Font &font, unsigned margin, const Colors::Color &colorText, const Colors::Color &BackgroundColor, uint8_t encoding)
{
	#ifdef DEBUG
	_ksys_debug_puts("\nprint text:");
	_ksys_debug_puts(text.c_str());
	_ksys_debug_putc('\n');
	#endif

	const int w = (margin * 2) + font.size.x;
	const int h = (margin * 2) + (font.size.y * text.length());

	Images::img canvas(BackgroundColor, {w, h});

	void *buff = drawTextToBuff(
		canvas.GetColorsMap(),
		w,
		h,
		margin,
		margin,
		text.c_str(),
		text.length(),
		font.size.x,
		font.size.y,
		colorText.val,
		font._Flags,
		encoding);

	canvas.SetColorMap((Colors::Color*)buff+8);

	free(buff);

	return canvas;
}