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

KolibriLib::Colors::Color::Color(ksys_color_t a)
{
    val = a;
}

Color &KolibriLib::Colors::Color::operator=(const Color &a)
{
    val = a.val;
    return *this;
}

Color &KolibriLib::Colors::Color::operator+(const Color &a)
{
    val /= 2;
    val += (a.val / 2);
    return *this;
}

bool KolibriLib::Colors::Color::operator==(const Color &a) const
{
    return val == a.val;
}

bool KolibriLib::Colors::Color::operator!=(const Color &a) const
{
    return val != a.val;
}
