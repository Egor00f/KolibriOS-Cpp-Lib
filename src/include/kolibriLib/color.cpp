#include "color.hpp"

using namespace KolibriLib;
using namespace Colors;

Color KolibriLib::Colors::BlendColors(const Color &a, const Color &b)
{
    Color result;
    result.red = (a.red + b.red) / 2; // Среднее арифметическое
    result.green = (a.green + b.green) / 2;
    result.blue = (a.blue + b.blue) / 2;
    return result;
}

bool KolibriLib::Colors::ComparisonColorsTables(const ColorsTable &a, const ColorsTable &b)
{
    return (a.frame_area == b.frame_area) && (a.grab_bar == b.grab_bar) && (a.grab_bar_button == b.grab_bar_button) && (a.grab_button_text == b.grab_button_text);
}
