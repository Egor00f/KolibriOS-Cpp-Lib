#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/color.hpp>

namespace KolibriLib
{
	// Графика
	namespace graphic
	{
		/// @brief Нарисовать линию
		/// @param a точка первая
		/// @param b точка вторая
		/// @param color Цвет линии
		inline void DrawLine(const Coord &coord, const Coord &b, const Colors::Color &color = OS::GetSystemColors().work_graph)
		{
			_ksys_draw_line(coord.x, coord.y, b.x, b.y, color.val);
		}

		/// @brief Нарисовать линию
		/// @param coord Координата от которой рисуется линия
		/// @param lenght Длина линии
		/// @param angle Угол
		/// @param color Цвет линии
		inline void DrawLine(const Coord &coord, unsigned lenght, unsigned short angle, const Colors::Color &color = OS::GetSystemColors().work_graph)
		{
			_ksys_draw_line(coord.x, coord.y, coord.x + (lenght * cos(angle)), coord.y + (lenght * sin(angle)), color.val);
		}

		/// @brief Закрасить пиксель точку
		/// @param position координаты
		/// @param color Цвет
		inline void DrawPixel(const Coord &position, const Colors::Color &color = OS::GetSystemColors().work_graph)
		{
			_ksys_draw_pixel(position.x, position.y, color.val);
		}

		/// @brief Нарисовать окружность
		/// @param coord Координаты центра
		/// @param Radius радиус окружности
		/// @param detalization Детализация прорисовки окружности (то на сколько круг круглый)
		/// @param color Цвет
		/// @paragraph Круг рисуется по detalization линий. Да-да если Детализация = 4, то круг это квадрат.
		void DrawCircle(const Coord& coord, const unsigned &Radius, const unsigned &detalization = 36, const Colors::Color& color = OS::GetSystemColors().work_graph);

		/// @brief Нарисовать закрашенный прямоугольник
		/// @param position позиция левого верхнего угла
		/// @param size Размеры
		/// @param color Цвет
		inline void DrawRectangleFill(Coord position, Size size, Colors::Color color = OS::GetSystemColors().work_graph)
		{
			__asm__ __volatile__(
				"int $0x40"
				:
				: "a"(13), 
				"b"( (position.x << 16) + size.x ), 
				"c"( (position.y << 16) + size.y ), 
				"d"(color.val)
				);
		}

		/// @brief Нарисовать круг(закрашенный)
		/// @param coord Координаты центра
		/// @param Radius Радиус круга
		/// @param detalization Детализация круга(то на сколько круг круглый)
		/// @param color Цвет
		void DrawCircleFill(const Coord& coord, const unsigned& Radius, const unsigned& detalization = 36, const Colors::Color& color = OS::GetSystemColors().work_graph);

		/// @brief Нарисовать точку
		/// @param position Координаты
		/// @param size Радиус точки в рx
		/// @param color Цвет
		/// @param fill Закрашенная/Выколотая точка
		void DrawPoint(const Coord& position, const unsigned& size, const Colors::Color& color = OS::GetSystemColors().work_graph, bool fill = false);


		/// @brief Нарисовать прямоугольник
		/// @param a Точка в левом верхнем углу
		/// @param b Точка в правом нижнем углу
		inline void DrawRectangleLines(const Coord &a, const Coord &b, const Colors::Color &color = OS::GetSystemColors().work_graph)
		{
			DrawLine(a, {b.x, a.y}, color);
			DrawLine(a, {a.x, b.y}, color);
			DrawLine({b.x, a.y}, b, color);
			DrawLine({a.x, b.y}, b, color);
		}

		/// @brief Нарисовать треугольник
		/// @param a первая точка
		/// @param b вторая точка
		/// @param c третья точка
		/// @param color цвет линий
		inline void DrawTriangle(const Coord &a, const Coord &b, const Coord &c, const Colors::Color &color = OS::GetSystemColors().work_graph)
		{
			DrawLine(a, b, color);
			DrawLine(a, c, color);
			DrawLine(b, c, color);
		}

		/// @brief прочитать цвет точки
		/// @param Point 
		/// @return
		inline Colors::Color ReadPoint(const Coord Point)
		{
			ksys_color_t c;

			__asm__ __volatile__(
				"int $0x40"
				: "=a"(c)
				: "a"(35),
				  "b"((Point.x * GetScreenSize().x + Point.y)));

			return (Colors::Color)c;
		}

		inline rgb_t* ReadArea(const Coord &coord, const Size &size)
		{
			rgb_t* result = new rgb_t[size.x * size.y];

			asm_inline (
				"int $0x40"
				::"a"(36), 
				"b"(result), 
				"c"(X_Y(size.x, size.y)), 
				"d"(X_Y(coord.x, coord.y))
			);

			return result;
		}


		//Почему то линковщик ругается "undefined reference cos()"

		inline void DrawCircle(const Coord &coord, const unsigned &Radius, const unsigned &detalization, const Colors::Color &color)
		{
			Coord buff;
			unsigned b = Radius;
			unsigned c = 0;

			for (unsigned angle = 1; angle <= detalization * 10; angle += 36 / detalization)
			{
				buff = Size(coord.x + (int)b, coord.y + (int)c);

				b = Radius * cos(angle);
				c = Radius * sin(angle);

				Coord n(coord.x + (int)b, coord.y + (int)c);

				DrawLine(buff, n);
			}
		}

		inline void DrawCircleFill(const Coord &coord, const unsigned &Radius, const unsigned &detalization, const Colors::Color &color)
		{
			DrawCircle(coord, Radius, detalization, color);

			unsigned b = Radius * cos(90 + 45);
			unsigned c = Radius * sin(90 + 45);
			Coord n(coord.x + (int)b, coord.y + (int)c);

			DrawRectangleFill(n, Size((coord.x - n.x) * 2, c * 2), color);

			for (unsigned i = Radius; i > (Radius - (coord.x - n.x)); i--) // Дозакрашивание пробелов между квадратом и границами груга
			{
				DrawCircle(coord, i, detalization, color);
			}
		}
	}

} // namespace KolibriLib


#endif // __GRAPHIC_H__