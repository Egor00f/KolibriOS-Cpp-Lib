#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;


void text::DrawText(Coord coord, const std::string &text, Font font)
{
	FreeType::DrawText(coord, text, font._face);
}
