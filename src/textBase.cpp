#include <kolibriLib/UI/textBase.hpp>

using namespace KolibriLib::UI;
using namespace text;


Images::img &KolibriLib::UI::text::DrawTextToImg(const std::string &text, const Fonts::Font &font, unsigned margin, const Colors::Color &colorText, const Colors::Color &BackgroundColor)
{
	const unsigned w = ((margin * 2) + font.size.x);
	const unsigned h = ((margin * 2) + (font.size.y * text.length()));

	Images::img canvas;
	Images::img buff;

	if (BackgroundColor._a < 1)
	{ // прозрачность фона
		const float k = BackgroundColor._a / 255;
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; i++)
			{
				canvas.SetPixel(Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + (int)margin + Coord(0, i) + Coord(j, 0)),
													BackgroundColor,
													k),
													i,
													j);
			}
		}
	}
	else
	{
		canvas.FillColor(BackgroundColor);
	}

	buff = canvas;

	drawText(canvas.GetRGBMap(), margin, margin, text.c_str(), text.length(), colorText.val, font._Flags);

	if (colorText._a < 1)
	{ // Прозрачность текста
		const float k = colorText._a / 255;
		for (int i = margin; i < w - margin; i++) // Трогать поля нет смысла
		{
			for (int j = margin; j < h - margin; i++)
			{
				if (buff != canvas)	// Если цвет пикселя отличается от фона
				{
					canvas.SetPixel(Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + (int)margin + Coord(0, i) + Coord(j, 0)),
														canvas.GetPixel(i, j),
														k),
									i,
									j);
				}
			}
		}
	}

	return canvas;
}