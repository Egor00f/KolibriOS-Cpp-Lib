#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/img.hpp>

using namespace KolibriLib;
using namespace graphic;

void graphic::DrawPoint(const Coord &position, const unsigned &size, const Colors::Color &color, bool fill)
{
	fill = !(size < 4); // если круг такого размера то будет ли он закрашен не будет даже видно

	if (!fill)
	{
		graphic::DrawCircle(position, size, color);
	}
	else
	{
		graphic::DrawCircleFill(position, size, color);
	}
}

void graphic::DrawCircle(const Coord &coord, unsigned Radius, const Colors::Color &color)
{
	UI::Images::img buff(
		Colors::Color(),
		{(static_cast<int>(Radius) * 2),
		 (static_cast<int>(Radius) * 2)},
		UI::Images::img::BPP::RGBA);

	buff.DrawCircle(
		{static_cast<int>(Radius),
		 static_cast<int>(Radius)},
		Radius,
		color);

	buff.Draw(coord);
}

void graphic::DrawCircleFill(const Coord &coord, const unsigned &Radius, const Colors::Color &color)
{
	// хаспде какой всратый алгоритм

	graphic::DrawCircle(coord, Radius, color);

	auto c = lround(Radius * sin(90 + 45));
	Coord n(coord.x + lround(Radius * cos(90 + 45)), coord.y + c);

	DrawRectangleFill(
		n,
		{(coord.x - n.x) * 2,
		 c * 2},
		color);

	for (unsigned i = Radius; i > static_cast<unsigned>(Radius - (coord.x - n.x)); i--) // Дозакрашивание пробелов между квадратом и границами груга
	{
		graphic::DrawCircle(coord, i, color);
	}
}