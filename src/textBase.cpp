#include <kolibriLib/UI/text/textBase.hpp>

using namespace KolibriLib::UI;
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
rgb_t *DrawTextToRGBMap(const rgb_t *canvas, int canvasWidth, int canvasHeight, int x, int y, const char *string, uint8_t width, uint8_t height, ksys_color_t fontColor, uint8_t flags, uint8_t encoding = Rasterworks_UTF8)
{
	const int l = canvasHeight * canvasHeight * sizeof(rgb_t) * sizeof(char);

	rgb_t *buff = (rgb_t *)malloc(l+8);
	*((int *)buff) = canvasWidth;
	*((int *)buff + 1) = canvasHeight;
	memcpy(buff + 8, canvas, l);

	drawText(buff, x, y, string, countUTF8Z(string, -1), fontColor, (flags >> 24) + (width >> 16) + (height >> 8) + encoding);

	rgb_t *res = (rgb_t*) malloc(l);

	memcpy(res, buff + 8, l);

	free(buff);

	return res;
}

Images::img *KolibriLib::UI::text::DrawTextToImg(const std::string &text, const Fonts::Font &font, unsigned margin, const Colors::Color &colorText, const Colors::Color &BackgroundColor, uint8_t encoding)
{
	#ifdef DEBUG
	_ksys_debug_puts("\nprint text:");
	_ksys_debug_puts(text.c_str());
	_ksys_debug_putc('\n');
	#endif

	const int w = ((margin * 2) + font.size.x);
	const int h = ((margin * 2) + (font.size.y * text.length()));

	Images::img canvas (BackgroundColor, Size(w, h));

	// if (BackgroundColor._a != 0xFF)
	// { // прозрачность фона
	// 	#ifdef DEBUG
	// 	_ksys_debug_puts("Background transp\n");
	// 	#endif
	// 	const float k = BackgroundColor._a / 255;
	// 	for (int i = 0; i < w; i++)
	// 	{
	// 		for (int j = 0; j < h; i++)
	// 		{
	// 			canvas->SetPixel(Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + (int)margin + Coord(0, i) + Coord(j, 0)),
	// 												BackgroundColor,
	// 												k),
	// 												i,
	// 												j);
	// 		}
	// 	}
	// }
	// else
	// {
		canvas.FillColor(BackgroundColor);
	// }

	rgb_t *b = canvas.GetRGBMap();


	Images::img buff(canvas);

	canvas.SetRGBMap(DrawTextToRGBMap(b, canvas.GetSize().x, canvas.GetSize().y, margin, margin, text.c_str(), font.size.x, font.size.y, colorText.val, font._Flags),
					  Size(w, h));

	delete[] b;

	// if (colorText._a != 0xFF && false)
	// { // Прозрачность текста
	// 	#ifdef DEBUG
	// 	_ksys_debug_puts("Text Transparency");
	// 	#endif
	// 	const float k = colorText._a / 255;
	// 	for (int i = margin; i < h - margin; i++) // Трогать поля нет смысла
	// 	{
	// 		for (int j = margin; j < w - margin; i++)
	// 		{
	// 			if (buff.GetPixel(i, j) != canvas->GetPixel(i, j))	// Если цвет пикселя отличается от фона
	// 			{
	// 				canvas->SetPixel(Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + (int)margin + Coord(0, i) + Coord(j, 0)),
	// 													buff.GetPixel(i, j),
	// 													k),
	// 								i,
	// 								j);
	// 			}
	// 		}
	// 	}
	// }

	Images::img *ret = new Images::img(canvas);
	return ret;
}