#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <fstream>

#include "os.hpp"
#include "small.hpp"
#include "filesystem.hpp"

namespace KolibriLib
{
    /// @brief различные графические примитивы
    namespace graphic
    {
        
        /// @brief Нарисовать линию
        /// @param a точка первая
        /// @param b точка вторая
        inline void DrawLine(const point<int> &a, const point<int> &b, const ksys_color_t color = OS::sys_color_table.work_graph)
        {
            _ksys_draw_line(a.x, a.y, b.x, b.y, color);
        }

        
        /// @brief Закрасить пиксель точку
        /// @param position координаты
        /// @param color Цвет
        inline void DrawPixel(const point<int> &position, const ksys_color_t color = OS::sys_color_table.work_text)
        {
            _ksys_draw_pixel(position.x, position.y, color);
        }

        /// @brief Нарисовать окружность
        /// @param coord Координаты центра
        /// @param Radius радиус окружности
        /// @param detalization Детализация прорисовки окружности, кол-во отрезков состовляющих окружность
        /// @paragraph Круг рисуется с помошью линий
        /// @param color Цвет
        void DrawCircle(const point<int>& coord, const unsigned& Radius, const unsigned& detalization = 36, ksys_color_t color = OS::sys_color_table.work_graph)
        {
            point<int> buff;
            int b = Radius;
            int c = 0;
            for (unsigned angle = 1; angle <= detalization * 10; angle += (36 / detalization))
            {
                buff = {coord.x + b, coord.y + c};
                b = Radius * cos(angle);
                c = Radius * sin(angle);
                point<int> n = {coord.x + b, coord.y + c};
                DrawLine(buff, n);
            }
        }

        /// @brief Нарисовать закрашенный прямоугольник
        /// @param position позиция левого верхнего угла
        /// @param size Размеры
        /// @param color Цвет
        void DrawRectangleFill(const point<int> &position, const point<int> &size, const ksys_color_t& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать круг(закрашенный)
        /// @param coord Координаты центра
        /// @param Radius Радиус круга
        /// @param color Цвет
        void DrawCircleFill(const point<int> &coord, const unsigned &Radius, const unsigned& detalization = 36, const ksys_color_t &color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param fill Закрашенная/Выколотая точка
        /// @paragraph Функция рисует закрашенную точку если fill = true
        void DrawPoint(const point<int> &position, const unsigned &Radius, const ksys_color_t &color = OS::sys_color_table.work_graph, bool fill = false);

        /// @brief Нарисовать прямоугольник
        /// @param a Точка в левом верхнем углу
        /// @param b Точка в правом нижнем углу
        void DrawRectangleLines(point<unsigned> a, point<unsigned> b, ksys_color_t color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать треугольник
        /// @param a первая точка
        /// @param b вторая точка
        /// @param c третья точка
        /// @param color цвет линий
        inline void DrawTriangle(point<unsigned> a, point<unsigned> b, point<unsigned> c, ksys_color_t color = OS::sys_color_table.work_graph);

        //=============================================================================================================================================================

        void DrawCircleFill(const point<int> &coord, const unsigned &Radius, const unsigned &detalization, const ksys_color_t &color)
        {
            DrawCircle(coord, Radius, color); // окружность
            int b = Radius * cos(90 + 45);    // В круге рисуется вписаный квадрат
            int c = Radius * sin(90 + 45);
            point<int> n = {coord.x + b, coord.y + c};
            DrawRectangleFill(n, {(coord.x - n.x) * 2, c * 2}, color);
            for (unsigned i = Radius; i > (Radius - (coord.x - n.x)); i -= 2) // Дозакрашивание пробелов между квадратом и границами груга
            {                                                                 // Тупо с помощью рисованию окружностей поменьше
                DrawCircle(coord, i, detalization, color);                    // Да, медленно, но мне лень думать
            }
        }

        void DrawPoint(const point<int> &position, const unsigned &Radius, const ksys_color_t &color, bool fill)
        {
            if (Radius < 3) // Если радиус меньше 3 пикселей, то не смысла его закрашивать
            {
                fill = false;
            }
            if (fill)
            {
                DrawCircleFill(position, Radius, color);
            }
            else
            {
                DrawCircle(position, Radius, color);
                if (Radius < 3)
                {
                    DrawPixel(position, color);
                }
            }
        }

        void DrawRectangleLines(point<int> a, point<int> b, ksys_color_t color)
        {
            DrawLine(a, {b.x, a.y}, color);
            DrawLine(a, {a.x, b.y}, color);
            DrawLine({b.x, a.y}, b, color);
            DrawLine({a.x, b.y}, b, color);
        }

        void DrawTriangle(point<int> a, point<int> b, point<int> c, ksys_color_t color)
        {
            DrawLine(a, b, color);
            DrawLine(a, c, color);
            DrawLine(b, c, color);
        }

        void DrawRectangleFill(const point<int> &position, const point<int> &size, const ksys_color_t &color)
        {
            __asm__ __volatile__(
                "int $0x40"
                :
                :"a"(13), "b"((position.x << 16) + size.x), "c"((position.y << 16) + size.y), "d"(color)
            );
        }
        //=============================================================================================================================================================

        
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__