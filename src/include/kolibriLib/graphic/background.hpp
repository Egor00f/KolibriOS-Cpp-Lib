#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <sys/ksys.h>

#include <stddef.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/UI/fonts.hpp>
#include <kolibri_rasterworks.h>

namespace KolibriLib
{
	/// @brief Работа с фоном
	namespace Background
	{
		bool f = false;

		/// @brief Получить размеры фонового изображения
		/// @return
		inline UI::Size GetSize()
		{
			ksys_pos_t p;
			asm_inline(
				"int $0x40"
				: "=a"(p)
				: "a"(39), "b"(1));

			return {(unsigned int)p.x, (unsigned int)p.y};
		}

		/// @brief Прочитать точку на фоне
		/// @param Point читаема точка
		/// @return
		inline Colors::Color ReadPoint(const UI::Coord &Point)
		{
			Colors::Color c;

			// Смещение
			unsigned s = GetSize().x * (Point.y - 1) + Point.x; // я думаю, что изображение это двумерный массив

			asm_inline(
				"int $0x40"
				: "=a"(c.val)
				: "a"(39), "b"(2), "c"(s));

			return c;
		}

		/// @brief Перерисовать фон
		inline void RedrawBackground()
		{
			_ksys_bg_redraw();
		}

		inline void RedrawBackground(const UI::Coord& coord, const UI::Size& size)
		{
			ksys_pos_t buff = coord.GetKsysPost();
			ksys_pos_t p2;
			p2.x = (unsigned)buff.x + size.GetKsysPost().x;
			p2.y = (unsigned)buff.y + size.GetKsysPost().y;
			_ksys_bg_redraw_bar(buff, p2);
		}

		inline void SetSize(const UI::Size &size)
		{
			f = true;
			_ksys_bg_set_size(size.x, size.y);
		}

		inline void DrawPoint(const UI::Coord coord, const Colors::Color &color)
		{
			if(!f)
			{
				SetSize(GetSize());
			}
			_ksys_bg_put_pixel(coord.x, coord.y, GetSize().x, color.val);
		}

		template <std::size_t N>
		inline void DrawImage(const UI::Coord coord, rgb_t (&rgb)[N])
		{
			if (!f)
			{
				SetSize(GetSize());
			}
			_ksys_bg_put_bitmap(rgb, sizeof(rgb_t) * N,  coord.x, coord.y, GetSize().x);
		}

		inline void DrawImage(const UI::Coord coord, rgb_t *rgb, std::size_t N)
		{
			if (!f)
			{
				SetSize(GetSize());
			}
			_ksys_bg_put_bitmap(rgb, sizeof(rgb_t) * N, coord.x, coord.y, GetSize().x);
		}

		/// @brief Нарисовать линию на фоне
		/// @param p1 точка перавая
		/// @param p2 точка вторая
		/// @param color цвет линии
		inline void DrawLine(const UI::Coord& p1, const UI::Coord& p2, const Colors::Color &color = OS::sys_color_table.work_graph)
		{
			for(int i = 0; i < abs(p1.x - p2.x); i++)
			{
				for (int j = 0; j < abs(p1.y - p2.y) / abs(p1.x - p2.x); j++)
				{
					DrawPoint(UI::Coord(p1.x + i, p1.y + j), color);
				}
			}
		}

		void DrawText(const std::string &text,
					  const UI::Coord &coord, const UI::text::Fonts::Font &font = UI::text::Fonts::DefaultFont,
					  unsigned margin = UI::DefaultMargin,
					  const Colors::Color &colorText = OS::sys_color_table.work_text,
					  const Colors::Color &BackgroundColor = OS::sys_color_table.work_area)
		{
			const unsigned w = ((margin * 2) + font.size.x);
			const unsigned h = ((margin * 2) + (font.size.y * text.length()));

			rgb_t *canvas = new rgb_t[w * h];

			for (int i = 0; i < w * h; i++)
			{
				canvas[i].red = BackgroundColor.red;
				canvas[i].blue = BackgroundColor.blue;
				canvas[i].green = BackgroundColor.green;
			}

			drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, font._Flags);
			DrawImage(coord, canvas, w * h);

			delete[] canvas;
		}

		

	} // namespace Background
	
} // namespace KolibriLib


#endif // __BACKGROUND_H__