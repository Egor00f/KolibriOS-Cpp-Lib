#ifndef __TEXTBASE_H__
#define __TEXTBASE_H__

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibri_rasterworks.h>
#include "fonts.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{
			/// \brief Получить размер текста
			/// \return текущая высота текста
			/// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
			inline unsigned int GetTextSize()
			{
				unsigned Size;
				asm_inline(
					"int $0x40"
					: "=c"(Size)
					: "a"(48), "b"(11));
				return Size;
			}

			/// \brief Изменить размер текста
			/// \param newSize высота текста в px
			/// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
			inline void SetTextSize(unsigned newSize)
			{
				asm_inline(
					"int $0x40" 
					::"a"(48), "b"(12), "c"(newSize)
				);
			}

			/// \brief Просто вывести текст
			/// \param text текст
			/// \param coord координаты
			/// \param color цвет текста
			/// @paragraph Для изменения высоты шрифта используйте @link SetTextSize(unsigned)
			inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::GetSystemColors().work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
			}

			/// @brief Вывести текст
			/// @param text Текст
			/// @param coord Координаты текста
			/// @param size Размеры символа(в px)
			/// @param flags Флаги
			/// @param margin Отступы границ фона от текста
			/// @param colorText Цвет текста
			/// @param BackgroundColor Цвет фона текста
			/// @paragraph Функция выводит текст, и фон текста, используя библиотеку RasterWorks
			/// @example DrawText("Text", {0,0}, Fonts::Font(Fonts::Arial, 16).size); //16 - высота шрифта
			/// @example DrawText("Text", {0,0}, Fonts::Font(Fonts::Michroma, 12, Italic).size); //16 - высота шрифта
			void DrawText(const std::string &text,
						  const Coord &coord, const Size &size = Fonts::DefaultFont.size,
						  unsigned flags = Flags::Normal,
						  unsigned margin = UI::DefaultMargin,
						  const Colors::Color &colorText = OS::GetSystemColors().work_text,
						  const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);
			

			/// @brief Вывести текст
			/// @param text Текст
			/// @param coord Координаты
			/// @param font Шрифт
			/// @param margin Отступы границ фона от текста
			/// @param colorText цвет текста
			/// @param BackgroundColor цвет фона
			/// @paragraph Функция выводить используя библиотеку RasterWorks
			void DrawText(const std::string &text,
						  const Coord &coord, const Fonts::Font &font = Fonts::DefaultFont,
						  unsigned margin = UI::DefaultMargin,
						  const Colors::Color &colorText = OS::GetSystemColors().work_text,
						  const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);
			
		}
	}
}

void KolibriLib::UI::text::DrawText(const std::string &text, const Coord &coord, const Size &size, unsigned flags, unsigned margin, const Colors::Color &colorText, const Colors::Color &BackgroundColor)
{
	const unsigned w = ((margin * 2) + size.x);
	const unsigned h = ((margin * 2) + (size.y * text.length()));

	rgb_t *canvas = new rgb_t[w * h];

	if (BackgroundColor._a < 1)
	{ // прозрачность фона
		const float k = BackgroundColor._a / 255;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; i++)
			{
				canvas[i * h + j] = Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0)),
														BackgroundColor,
														k)
										.GetRGB();
			}
		}
	}
	else
	{
		memset((void *)canvas, Colors::RGBtoINT(BackgroundColor.GetRGB()), w * h);
	}

	drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, flags);

	if (colorText._a < 1)
	{ // Прозрачность текста
		const float k = colorText._a / 255;
		for (int i = margin; i < h - margin; i++) // Трогать поля нет смысла
		{
			for (int j = margin; j < w - margin; i++)
			{
				Colors::Color b = graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0));
				if (b != canvas[i * (h - margin) + j])
				{
					canvas[i * (h - margin) + j] = Colors::BlendColors(b,
																	   canvas[i * (h - margin) + j],
																	   k)
													   .GetRGB();
				}
			}
		}
	}

	_ksys_draw_bitmap(canvas, coord.x, coord.y, w, h);

	delete[] canvas;
}

#endif // __TEXTBASE_H__