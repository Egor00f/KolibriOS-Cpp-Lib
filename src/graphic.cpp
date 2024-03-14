#include <kolibriLib/graphic/graphic.hpp>

using namespace KolibriLib;

void graphic::DrawCircle(const UI::Coord &coord, const unsigned &Radius, const unsigned &detalization, const Colors::Color &color)
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

void graphic::DrawCircleFill(const UI::Coord &coord, const unsigned &Radius, const unsigned &detalization, const Colors::Color &color)
{
	graphic::DrawCircle(coord, Radius, detalization, color);

	unsigned b = Radius * cos(90 + 45);
	unsigned c = Radius * sin(90 + 45);
	UI::Coord n = {coord.x + (int)b, coord.y + (int)c};

	DrawRectangleFill(n, {(unsigned)(coord.x - n.x) * 2, (unsigned)c * 2}, color);

	for (unsigned i = Radius; i > (Radius - (coord.x - n.x)); i--) // Дозакрашивание пробелов между квадратом и границами груга
	{
		graphic::DrawCircle(coord, i, detalization, color);
	}
}

void graphic::DrawPoint(const UI::Coord &position, const unsigned &size, const Colors::Color &color, bool fill)
{
	if (size < 3)
	{
		fill = false;
	}
	if (!fill)
	{
		graphic::DrawCircle(position, size, 8, color);
	}
	else
	{
		graphic::DrawCircleFill(position, size, 8, color);
	}
}