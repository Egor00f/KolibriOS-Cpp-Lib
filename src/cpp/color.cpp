#include <kolibriLib/color.hpp>
#include "color.hpp"

using namespace KolibriLib;
using namespace Colors;

KolibriLib::Colors::Color::Color(const ksys_color_t& a)
{
    val = a;
}

KolibriLib::Colors::Color::Color(const Color &a)
{
    val = a.val;
}

KolibriLib::Colors::Color::Color(const ARGB & a)
{
    _a      = a.alpha;
    red     = a.red;
    green   = a.green;
    blue    = a.blue;
}

Color &KolibriLib::Colors::Color::operator=(const Color &a)
{
    val = a.val;
    return *this;
}

Color &KolibriLib::Colors::Color::operator+(const Color &a)
{
    _a /= 2;
    _a += a._a / 2;
    red /= 2;
    red += (a.red / 2);
    green /= 2;
    green += (a.green / 2);
    blue /= 2;
    blue += (a.blue / 2);
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

KolibriLib::Colors::ColorsTable::ColorsTable(ksys_colors_table_t table)
{
    work_area = table.work_area;
    work_button = table.work_button;
    work_button_text = table.work_button_text;
    work_graph = table.work_graph;
    work_text = table.work_text;
}

bool KolibriLib::Colors::ColorsTable::operator==(const ColorsTable &table) const
{
    return (frame_area == table.frame_area) &&
           (grab_bar == table.grab_bar) &&
           (grab_bar_button == table.grab_bar_button) &&
           (grab_button_text == table.grab_button_text) &&
           (work_area == table.work_area) &&
           (work_button == table.work_button) &&
           (work_button_text == table.work_button_text) &&
           (work_graph == table.work_graph) &&
           (work_text == table.work_text);
}

bool KolibriLib::Colors::ColorsTable::operator!=(const ColorsTable &table) const
{
    return (frame_area          != table.frame_area) ||
           (grab_bar            != table.grab_bar) ||
           (grab_bar_button     != table.grab_bar_button) ||
           (grab_button_text    != table.grab_button_text) ||
           (work_area           != table.work_area) ||
           (work_button         != table.work_button) ||
           (work_button_text    != table.work_button_text);
}
Color KolibriLib::Colors::BlendColors(const Color &a, const Color &b, const float k)
{
	Color buff;
    buff._a     = (a._a    * static_cast<int>(k)) + (b._a    * (1 - static_cast<int>(k)));
    buff.red    = (a.red   * static_cast<int>(k)) + (b.red   * (1 - static_cast<int>(k)));
    buff.green  = (a.green * static_cast<int>(k)) + (b.green * (1 - static_cast<int>(k)));
    buff.blue   = (a.blue  * static_cast<int>(k)) + (b.blue  * (1 - static_cast<int>(k)));
    return buff;
}