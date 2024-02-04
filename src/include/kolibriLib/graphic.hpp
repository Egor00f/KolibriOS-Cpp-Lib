#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__


#include <sys/ksys.h>
#include <stdio.h>
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
        void DrawCircle(const UI::Coord& coord, const unsigned& Radius, const unsigned& detalization = 36, const Color::Color& color = OS::sys_color_table.work_graph);

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
        void DrawCircleFill(const UI::Coord& coord, const unsigned& Radius, const unsigned& detalization = 36, const Color::Color& color = OS::sys_color_table.work_graph);

        /// @brief Нарисовать точку
        /// @param position Координаты
        /// @param size Радиус точки в рx
        /// @param color Цвет
        /// @param fill Закрашенная/Выколотая точка
        void DrawPoint(const UI::Coord&position, const unsigned& size, const Color::Color& color = OS::sys_color_table.work_graph, bool fill = false);


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
} // namespace KolibriLib


#endif // __GRAPHIC_H__