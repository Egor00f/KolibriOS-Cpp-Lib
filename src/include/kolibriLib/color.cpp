#include "color.hpp"

using namespace KolibriLib;
using namespace Colors;

KolibriLib::Colors::Color::Color(ksys_color_t a)
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

KolibriLib::Colors::ColorsTable::ColorsTable(ksys_colors_table_t table)
{
    work_area = table.work_area;
    work_button = table.work_button;
    work_button_text = table.work_button_text;
}

bool KolibriLib::Colors::ColorsTable::operator==(const ColorsTable &table) const
{
    return (frame_area == table.frame_area) &&
           (grab_bar == table.grab_bar) &&
           (grab_bar_button == table.grab_bar_button) &&
           (grab_button_text == table.grab_button_text) &&
           (work_area == table.work_area) &&
           (work_button == table.work_button);
}

bool KolibriLib::Colors::ColorsTable::operator!=(const ColorsTable &table) const
{
    return (frame_area          != table.frame_area) &&
           (grab_bar            != table.grab_bar) &&
           (grab_bar_button     != table.grab_bar_button) &&
           (grab_button_text    != table.grab_button_text) &&
           (work_area           != table.work_area) &&
           (work_button         != table.work_button);
}