#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "base.hpp"
#include "UI.hpp"
#include "color.hpp"

namespace KolibriLib
{
    // Графика
    namespace graphic
    {
        /// @brief Нарисовать линию
        /// @param a точка первая
        /// @param b точка вторая
        /// @param color Цвет линии
        inline void DrawLine(UI::Coord a, UI::Coord b, Color::Color color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_line(a.x, a.y, b.x, b.y, color);
        }

        /// @brief Закрасить пиксель точку
        /// @param position координаты
        /// @param color Цвет
        inline void DrawPixel(UI::Coord position, Color::Color color)
        {
            _ksys_draw_pixel(position.x, position.y, color);
        }

        /// @brief Нарисовать окружность
        /// @param coord Координаты центра
        /// @param Radius радиус окружности
        /// @param detalization Детализация прорисовки окружности (то на сколько круг круглый)
        /// @param color Цвет
        void DrawCircle(UI::Coord coord, unsigned Radius, unsigned detalization = 36, Color::Color color = OS::sys_color_table.work_graph)
        {
            UI::Coord buff;
            unsigned b = Radius;
            unsigned c = 0;
            for (unsigned angle = 1; angle <= detalization * 10; angle += 36 / detalization)
            {
                buff = {coord.x + (int)b, coord.y + (int)c};
                b = Radius * cos(angle);
                c = Radius * sin(angle);
                UI::Coord n = {coord.x + (int)b, coord.y + (int)c};
                DrawLine(buff, n);
            }
        }

        /// @brief Нарисовать закрашенный прямоугольник
        /// @param position позиция левого верхнего угла
        /// @param size Размеры
        /// @param color Цвет
        void DrawRectangleFill(UI::Coord position, UI::Size size, Color::Color color = OS::sys_color_table.work_graph)
        {
            __asm__ __volatile__(
                "int $0x40" ::"a"(13), "b"((position.x << 16) + size.x), "c"((position.y << 16) + size.y), "d"(color));
        }

        /// @brief Нарисовать круг(закрашенный)
        /// @param coord Координаты центра
        /// @param Radius Радиус круга
        /// @param detalization Детализация круга(то на сколько круг круглый)
        /// @param color Цвет
        void DrawCircleFill(UI::Coord coord, unsigned Radius, unsigned detalization = 36, Color::Color color = OS::sys_color_table.work_graph)
        {
            DrawCircle(coord, Radius, color);

            unsigned b = Radius * cos(90+45);
            unsigned c = sqrt((Radius * Radius) - (b * b));
            UI::Coord n = {coord.x + (int)b, coord.y + (int)c};

            DrawRectangleFill(n, {(unsigned)(coord.x - n.x) * 2, (unsigned)c * 2}, color);

            for (unsigned i = Radius; i > (Radius -(coord.x - n.x)); i--)//Дозакрашивание пробелов между квадратом и границами груга
            {
                DrawCircle(coord, i, detalization, color);
            }
        }

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param a Закрашенная/Выколотая точка
        void DrawPoint(UI::Coord position, unsigned size, Color::Color color = OS::sys_color_table.work_graph, bool a = false)
        {
            if(size < 3)
            {
                a = true;
            }
            if (a)
            {
                DrawCircle(position, size, color);
            }
            else
            {
                DrawCircleFill(position, size, color);
            }
        }


        /// @brief Нарисовать прямоугольник
        /// @param a Точка в левом верхнем углу
        /// @param b Точка в правом нижнем углу
        void DrawRectangleLines(UI::Coord a, UI::Coord b, Color::Color color = OS::sys_color_table.work_graph)
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
        inline void DrawTriangle(UI::Coord a, UI::Coord b, UI::Coord c, Color::Color color = OS::sys_color_table.work_graph)
        {
            DrawLine(a, b, color);
            DrawLine(a, c, color);
            DrawLine(b, c, color);
        }
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__