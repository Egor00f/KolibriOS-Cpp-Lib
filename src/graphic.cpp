#include <kolibriLib/graphic/graphic.hpp>

using namespace KolibriLib;



void graphic::DrawPoint(const Coord &position, const unsigned &size, const Colors::Color &color, bool fill)
{
	if(size < 4)
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