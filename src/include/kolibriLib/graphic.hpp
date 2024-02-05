#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "small.hpp"
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
        inline void DrawLine(const UI::Coord& coord, const UI::Coord& b, const Color::Color& color = OS::sys_color_table.work_graph);
        

        /// @brief Нарисовать линию
        /// @param coord Координата от которой рисуется линия
        /// @param lenght Длина линии
        /// @param angle Угол
        /// @param color Цвет линии
        inline void DrawLine(const UI::Coord &coord, unsigned lenght, unsigned short angle, const Color::Color &color = OS::sys_color_table.work_graph);

        /// @brief Закрасить пиксель точку
        /// @param position координаты
        /// @param color Цвет
        inline void DrawPixel(const UI::Coord& position, const Color::Color& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать окружность
        /// @param coord Координаты центра
        /// @param Radius радиус окружности
        /// @param detalization Детализация прорисовки окружности (то на сколько круг круглый)
        /// @param color Цвет
        /// @paragraph Круг рисуется по detalization линий. Да-да если Детализация = 4, то круг это квадрат.
        void DrawCircle(const UI::Coord& coord, unsigned Radius, unsigned detalization = 36, const Color::Color& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать закрашенный прямоугольник
        /// @param position позиция левого верхнего угла
        /// @param size Размеры
        /// @param color Цвет
        void DrawRectangleFill(UI::Coord position, UI::Size size, Color::Color color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать круг(закрашенный)
        /// @param coord Координаты центра
        /// @param Radius Радиус круга
        /// @param detalization Детализация круга(то на сколько круг круглый)
        /// @param color Цвет
        void DrawCircleFill(const UI::Coord& coord, unsigned Radius, unsigned detalization = 36, const Color::Color& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param fill Закрашенная/Выколотая точка
        void DrawPoint(const UI::Coord& position, const unsigned& size, const Color::Color& color = OS::sys_color_table.work_graph, bool fill = false);


        /// @brief Нарисовать прямоугольник
        /// @param a Точка в левом верхнем углу
        /// @param b Точка в правом нижнем углу
        inline void DrawRectangleLines(const UI::Coord& a, const UI::Coord& b, const Color::Color& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать треугольник
        /// @param a первая точка
        /// @param b вторая точка
        /// @param c третья точка
        /// @param color цвет линий
        inline void DrawTriangle(const UI::Coord& a, const UI::Coord& b, const UI::Coord& c, const Color::Color& color = OS::sys_color_table.work_graph);
    }
    void graphic::DrawLine(const UI::Coord &coord, const UI::Coord &b, const Color::Color &color)
    {
        _ksys_draw_line(coord.x, coord.y, b.x, b.y, color.val);
    }

    void graphic::DrawLine(const UI::Coord &coord, unsigned lenght, unsigned short angle, const Color::Color &color)
    {
        _ksys_draw_line(coord.x, coord.y, coord.x + (lenght * cos(angle)), coord.y + (lenght * sin(angle)), color.val);
    }

    void graphic::DrawPixel(const UI::Coord &position, const Color::Color &color)
    {
        _ksys_draw_pixel(position.x, position.y, color.val);
    }

    void graphic::DrawCircle(const UI::Coord &coord, unsigned Radius, unsigned detalization, const Color::Color &color)
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

    void graphic::DrawCircleFill(const UI::Coord &coord, unsigned Radius, unsigned detalization, const Color::Color &color)
    {
        DrawCircle(coord, Radius, detalization, color);

        unsigned b = Radius * cos(90 + 45);
        unsigned c = Radius * sin(90 + 45);
        UI::Coord n = {coord.x + (int)b, coord.y + (int)c};

        DrawRectangleFill(n, {(unsigned)(coord.x - n.x) * 2, (unsigned)c * 2}, color);

        for (unsigned i = Radius; i > (Radius - (coord.x - n.x)); i--) // Дозакрашивание пробелов между квадратом и границами груга
        {
            DrawCircle(coord, i, detalization, color);
        }
    }

    void graphic::DrawRectangleFill(UI::Coord position, UI::Size size, Color::Color color)
    {
        __asm__ __volatile__(
            "int $0x40"
            :
            : "a"(13), "b"((position.x << 16) + size.x), "c"((position.y << 16) + size.y), "d"(color.val));
    }

    void graphic::DrawPoint(const UI::Coord &position, const unsigned &size, const Color::Color &color, bool fill)
    {
        if (size < 3)
        {
            fill = true;
        }
        if (fill)
        {
            DrawCircle(position, size, color.val);
        }
        else
        {
            DrawCircleFill(position, size, color.val);
        }
    }

    void graphic::DrawRectangleLines(const UI::Coord &a, const UI::Coord &b, const Color::Color &color)
    {
        DrawLine(a, {b.x, a.y}, color);
        DrawLine(a, {a.x, b.y}, color);
        DrawLine({b.x, a.y}, b, color);
        DrawLine({a.x, b.y}, b, color);
    }

    void graphic::DrawTriangle(const UI::Coord &a, const UI::Coord &b, const UI::Coord &c, const Color::Color &color)
    {
        DrawLine(a, b, color);
        DrawLine(a, c, color);
        DrawLine(b, c, color);
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__