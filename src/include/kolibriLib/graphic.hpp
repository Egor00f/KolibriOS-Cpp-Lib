#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "base.hpp"

namespace KolibriLib
{
    // Графика
    namespace graphic
    {
        /// @brief Нарисовать линию
        /// @param a точка первая
        /// @param b точка вторая
        inline void DrawLine(point a, point b, ksys_color_t color = window::colors.work_graph)
        {
            _ksys_draw_line(a.x, a.y, b.x, b.y, color);
        }

        /// @brief Закрасить пиксель точку
        /// @param position координаты
        /// @param color Цвет
        inline void DrawPixel(point position, ksys_color_t color)
        {
            _ksys_draw_pixel(position.x, position.y, color);
        }

        /// @brief Нарисовать окружность
        /// @param coord Координаты центра
        /// @param Radius радиус окружности
        /// @param detalization Детализация прорисовки окружности
        /// @param color Цвет
        void DrawCircle(point coord, unsigned Radius, unsigned detalization = 36, ksys_color_t color = window::colors.work_graph)
        {
            point buff;
            unsigned b = Radius;
            unsigned c = 0;
            for (unsigned angle = 1; angle <= detalization * 10; angle += 36 / detalization)
            {
                buff = {coord.x + b, coord.y + c};
                b = Radius * cos(angle);
                c = sqrt((Radius*Radius) - (b*b));
                point n = {coord.x + b, coord.y + c};
                DrawLine(buff, n);
            }
        }

        /// @brief Нарисовать закрашенный прямоугольник
        /// @param position позиция левого верхнего угла
        /// @param size Размеры
        /// @param color Цвет
        void DrawRectangleFill(point position, point size, ksys_color_t color = window::colors.work_graph)
        {
            position.x *= AAANUMBER;
            position.y *= AAANUMBER;

            __asm__ __volatile__(
                "int $0x40" ::"a"(13), "b"(position.x + size.x), "c"(position.y + size.y), "d"(color));
        }

        /// @brief Нарисовать круг(закрашенный)
        /// @param coord Координаты центра
        /// @param Radius Радиус круга
        /// @param color Цвет
        void DrawCircleFill(point coord, unsigned Radius, ksys_color_t color = window::colors.work_graph)
        {
            DrawCircle(coord, Radius, color);
            unsigned b = Radius * cos(90+45);
            unsigned c = sqrt((Radius * Radius) - (b * b));
            point n = {coord.x + b, coord.y + c};
            DrawRectangleFill(n, {(coord.x - n.x) * 2, c * 2}, color);
            for (unsigned i = Radius; i > (Radius -(coord.x - n.x)); i--)//Дозакрашивание пробелов между квадратом и границами груга
            {
                DrawCircle(coord, i, NULL, color);
            }
        }

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param a Закрашенная/Выколотая точка
        inline void DrawPoint(point position, unsigned size, ksys_color_t color = window::colors.work_graph, bool a = false)
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
        void DrawRectangleLines(point a, point b, ksys_color_t color = window::colors.work_graph)
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
        inline void DrawTriangle(point a, point b, point c, ksys_color_t color = window::colors.work_graph)
        {
            DrawLine(a, b, color);
            DrawLine(a, c, color);
            DrawLine(b, c, color);
        }
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__