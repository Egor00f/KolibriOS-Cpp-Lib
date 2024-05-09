#include <kolibriLib/graphic/graphic.hpp>

using namespace KolibriLib;
using namespace graphic;


void graphic::DrawPoint(const Coord &position, const unsigned &size, const Colors::Color &color, bool fill)
{
	if(size < 4)
	{
		fill = false;
	}
	if (!fill)
	{
		graphic::DrawCircle(position, size, color);
	}
	else
	{
		graphic::DrawCircleFill(position, size, color);
	}
}

void DrawCircle(const Coord &coord, unsigned Radius, const Colors::Color &color)
{
	UI::Images::img buff(Colors::Color(), {((int)Radius * 2), ((int)Radius * 2)}, UI::Images::img::RGBA);
	buff.DrawCircle({(int)Radius, (int)Radius}, Radius, color);
	buff.Draw(coord);
}

void DrawCircleFill(const Coord &coord, const unsigned &Radius, const Colors::Color &color)
{
	graphic::DrawCircle(coord, Radius, color);

	unsigned b = Radius * cos(90 + 45);
	unsigned c = Radius * sin(90 + 45);
	Coord n(coord.x + (int)b, coord.y + (int)c);

	DrawRectangleFill(n, {(coord.x - n.x) * 2, (int)c * 2}, color);

	for (unsigned i = Radius; i > (Radius - (coord.x - n.x)); i--) // Дозакрашивание пробелов между квадратом и границами груга
	{
		graphic::DrawCircle(coord, i, color);
	}
}