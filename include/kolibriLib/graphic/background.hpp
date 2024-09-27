#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include <include_ksys.h>

#include <stddef.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/img.hpp>
#include <kolibriLib/globals.hpp>

namespace KolibriLib
{
	/// @brief Работа с фоном
	namespace Background
	{

		/// @brief Получить размеры фонового изображения
		/// @return размер фонового изображения
		inline Size GetSize()
		{
			ksys_pos_t p;
			asm_inline (
				"int $0x40"
				: "=a"(p)
				: "a"(39), "b"(1)
			);

			return Size(p.x, p.y);
		}

		/// @brief Прочитать точку на фоне
		/// @param Point читаема точка
		/// @return Цвет точки
		inline Colors::Color ReadPoint(const Coord &Point)
		{
			Colors::Color c;

			// Смещение
			int s = GetSize().x * (Point.y - 1) + Point.x; // я думаю, что изображение это двумерный массив

			asm_inline (
				"int $0x40"
				: "=a"(c.val)
				: "a"(39), "b"(2), "c"(s)
			);

			return c;
		}

		/// @brief Перерисовать весь фон
		inline void RedrawBackground()
		{
			_ksys_bg_redraw();
		}

		/// @brief Перересовать область фона
		/// @param coord координаты верхненго левого угла области
		/// @param size размеры 
		inline void RedrawBackground(const Coord& coord, const Size& size)
		{
			_ksys_bg_redraw_bar(coord.operator ksys_pos_t(), (coord + size).operator ksys_pos_t());
		}

		/// @brief
		/// @param
		inline void SetSize(const Size &size)
		{
			_ksys_bg_set_size (
				static_cast<std::uint32_t>(size.x),
				static_cast<std::uint32_t>(size.y)
			);
		}

		/// @brief Постовить точку на фоне
		/// @param coord координаты точки
		/// @param color цвет точки
		inline void DrawPoint(const Coord coord, const Colors::Color &color = Globals::SystemColors.work_graph)
		{
			_ksys_bg_put_pixel (
				static_cast<std::uint32_t>(coord.x), 
				static_cast<std::uint32_t>(coord.y), 
				static_cast<std::uint32_t>(GetSize().x), 
				color.operator ksys_color_t()
			);
		}

		template <std::size_t N>
		/// @brief
		/// @param coord
		/// @param rgb
		inline void DrawImage(const Coord coord, rgb_t (&rgb)[N])
		{
			_ksys_bg_put_bitmap(
				rgb,
				sizeof(rgb_t) * N,
				static_cast<std::uint32_t>(coord.x),
				static_cast<std::uint32_t>(coord.y),
				static_cast<std::uint32_t>(GetSize().x));
		}

		/// @brief Вывести изображение(rgb)
		/// @param coord координаты
		/// @param rgb массив
		/// @param N длинна массива rgb
		inline void DrawImage(const Coord &coord, rgb_t *rgb, std::size_t N)
		{
			_ksys_bg_put_bitmap(
				rgb,
				sizeof(rgb_t) * N,
				static_cast<std::uint32_t>(coord.x),
				static_cast<std::uint32_t>(coord.y),
				static_cast<std::uint32_t>(GetSize().x));
		}

		/// @brief Нарисовать линию на фоне
		/// @param p1 точка перавая
		/// @param p2 точка вторая
		/// @param color цвет линии
		inline void DrawLine(const Coord& p1, const Coord& p2, const Colors::Color &color = Globals::SystemColors.work_graph)
		{
			for(int i = 0; i < abs(p1.x - p2.x); i++)
			{
				for (int j = 0; j < abs(p1.y - p2.y) / abs(p1.x - p2.x); j++)
				{
					DrawPoint(Coord(p1.x + i, p1.y + j), color);
				}
			}
		}
	} // namespace Background
	
} // namespace KolibriLib


#endif // __BACKGROUND_H__