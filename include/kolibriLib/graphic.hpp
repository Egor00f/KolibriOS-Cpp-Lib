#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

namespace KolibriLib
{
    // Графика
    namespace graphic
    {
        /// @brief Нарисовать точку
        /// @param position координаты
        /// @param color цвет
        inline void DrawPoint(point position, ksys_color_t color)
        {
            _ksys_draw_pixel(position.x, position.y, color);
        }

        /// @brief Нарисовать линию
        /// @param a точка первая
        /// @param b точка вторая
        inline void Line(point a, point b, ksys_color_t color = window::colors.work_graph)
        {
            _ksys_draw_line(a.x, a.y, b.x, b.y, color);
        }

        /// @brief Нарисовать прямоугольник
        /// @param a Точка в левом верхнем углу
        /// @param b Точка в правом нижнем углу
        void DrawRectangleLines(point a, point b, ksys_color_t color = window::colors.work_graph)
        {
            Line(a, {b.x, a.y}, color);
            Line(a, {a.x, b.y}, color);
            Line({b.x, a.y}, b, color);
            Line({a.x, b.y}, b, color);
        }

        void DrawRectangleFill(point position, point size, ksys_color_t color = window::colors.work_graph)
        {
            position.x *= AAANUMBER;
            position.y *= AAANUMBER;

            __asm__ __volatile__(
                "int $0x40" ::"a"(13), "b"(position.x + size.x), "c"(position.y + size.y), "d"(color));
        }

        /// @brief Нарисовать треугольник
        /// @param a первая точка
        /// @param b вторая точка
        /// @param c третья точка
        /// @param color цвет линий
        inline void DrawTriangle(point a, point b, point c, ksys_color_t color = window::colors.work_graph)
        {
            Line(a, b, color);
            Line(a, c, color);
            Line(b, c, color);
        }
    }
} // namespace KolibriLib


#endif // __GRAPHIC_H__