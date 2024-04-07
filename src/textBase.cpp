#include <kolibriLib/UI/text/textBase.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

/// @brief Draw text on 24bpp or 32bpp image
/// @param canvas Pointer to image (array of colors)
/// @param canvasWidth image width
/// @param canvasHeight image height
/// @param x Coordinate of the text along the X axis
/// @param y Coordinate of the text along the Y axis
/// @param string Pointer to string
/// @param width char width (0 - auto)
/// @param height char height
/// @param fontColor Text color
/// @param flags value from enum RasterworksParams
/// @param encoding value fram enum RasterworksEncoding
/// @note don't forget free(buff)
rgb_t *DrawTextToRGBMap(const void *canvas, Size coord, int x, int y, const std::string &string, uint8_t width, uint8_t height, ksys_color_t fontColor, uint8_t flags, uint8_t encoding = Rasterworks_UTF8)
{
	const int l = coord.x * coord.y * 3;

	RasterWorksBuff *buff = (RasterWorksBuff *)malloc(l + 8);

	buff->width = coord.x;
	buff->height = coord.y;

	memcpy(buff + 8, canvas, l);

	drawText(buff,
			 coord.x,
			 coord.y, 
			 string.c_str(), 
			 string.length(),
			 fontColor, 
			 (flags << 24) + (width << 16) + (height << 8) + encoding);

	rgb_t *res = (rgb_t*) malloc(l);

	memcpy(res, buff + 8, l);

	free(buff);

	return res;
}

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

	rgb_t* buff = new rgb_t[w*h];

	buff = DrawTextToRGBMap(canvas.GetBuff()->buf_pointer, 
	                        {w, h}, 
							margin, margin, 
							text, 
							font.size.x, font.size.y, 
							colorText.val, 
							font._Flags);

	canvas.SetRGBMap(buff, {w, h});
		   
	delete[] buff;

	return canvas;
}