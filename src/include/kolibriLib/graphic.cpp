#include "graphic.hpp"

using namespace KolibriLib;

void graphic::DrawLine(const UI::Coord &coord, const UI::Coord &b, const Colors::Color &color)
{
    _ksys_draw_line(coord.x, coord.y, b.x, b.y, color.val);
}

void graphic::DrawLine(const UI::Coord &coord, unsigned lenght, unsigned short angle, const Colors::Color &color)
{
    _ksys_draw_line(coord.x, coord.y, coord.x + (lenght * cos(angle)), coord.y + (lenght * sin(angle)), color.val);
}

void graphic::DrawPixel(const UI::Coord &position, const Colors::Color &color)
{
    _ksys_draw_pixel(position.x, position.y, color.val);
}

void graphic::DrawCircle(const UI::Coord &coord, unsigned Radius, unsigned detalization, const Colors::Color &color)
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

void graphic::DrawCircleFill(const UI::Coord &coord, unsigned Radius, unsigned detalization, const Colors::Color &color)
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

void graphic::DrawRectangleFill(UI::Coord position, UI::Size size, Colors::Color color)
{
    __asm__ __volatile__(
        "int $0x40"
        :
        : "a"(13), "b"((position.x << 16) + size.x), "c"((position.y << 16) + size.y), "d"(color.val));
}

void graphic::DrawPoint(const UI::Coord &position, const unsigned &size, const Colors::Color &color, bool fill)
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

void graphic::DrawRectangleLines(const UI::Coord &a, const UI::Coord &b, const Colors::Color &color)
{
    DrawLine(a, {b.x, a.y}, color);
    DrawLine(a, {a.x, b.y}, color);
    DrawLine({b.x, a.y}, b, color);
    DrawLine({a.x, b.y}, b, color);
}

void graphic::DrawTriangle(const UI::Coord &a, const UI::Coord &b, const UI::Coord &c, const Colors::Color &color)
{
    DrawLine(a, b, color);
    DrawLine(a, c, color);
    DrawLine(b, c, color);
}