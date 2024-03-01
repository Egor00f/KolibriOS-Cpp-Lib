#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <sys/ksys.h>

#include <stddef.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>

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

		inline void RedrawBackground(const UI::Coord coord, const UI::Size size)
		{
			_ksys_bg_redraw_bar(coord.GetKsysPost(), size.GetKsysPost());
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
	} // namespace Background
	
} // namespace KolibriLib


#endif // __BACKGROUND_H__