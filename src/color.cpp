#include <kolibriLib/color.hpp>

using namespace KolibriLib;
using namespace Colors;

KolibriLib::Colors::Color::Color(const ksys_color_t &a)
{
	val = a;
}

KolibriLib::Colors::Color::Color(const KolibriLib::Colors::Color &a)
{
	val = a.val;
}

KolibriLib::Colors::Color::Color(const KolibriLib::Colors::ARGB &a)
{
	_a = a.alpha;
	red = a.red;
	green = a.green;
	blue = a.blue;
}

KolibriLib::Colors::Color::Color(const rgb_t &color)
{
	_a = 0xFF;
	red = color.red;
	green = color.green;
	red = color.blue;
}

rgb_t KolibriLib::Colors::Color::GetRGB() const
{
	return {red, green, blue};
}

KolibriLib::Colors::Color &KolibriLib::Colors::Color::operator=(const KolibriLib::Colors::Color &a)
{
	val = a.val;
	return *this;
}

Color &KolibriLib::Colors::Color::operator=(const uint32_t &color)
{
	val = color;
	return *this;
}

KolibriLib::Colors::Color &KolibriLib::Colors::Color::operator+(const KolibriLib::Colors::Color &a)
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
	frame_area = table.frame_area;
	grab_bar = table.grab_bar;
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
	return (frame_area != table.frame_area) ||
		   (grab_bar != table.grab_bar) ||
		   (grab_bar_button != table.grab_bar_button) ||
		   (grab_button_text != table.grab_button_text) ||
		   (work_area != table.work_area) ||
		   (work_button != table.work_button) ||
		   (work_button_text != table.work_button_text);
}

ksys_color_t KolibriLib::Colors::RGBtoINT(const rgb_t &color)
{
	return (color.blue << 16) + (color.green << 8) + color.red;
}

KolibriLib::Colors::Color KolibriLib::Colors::BlendColors(const KolibriLib::Colors::Color &a, const KolibriLib::Colors::Color &b, float k)
{
	if (k > 1.0) // Коэфицент более 1 не имеет смысла
		k = 1.0;

	// буффер
	KolibriLib::Colors::Color buff;

	buff._a		= static_cast<uint8_t>( (a._a    * k) + (b._a    * (1.0f - k)) );
	buff.red	= static_cast<uint8_t>( (a.red   * k) + (b.red   * (1.0f - k)) );
	buff.green	= static_cast<uint8_t>( (a.green * k) + (b.green * (1.0f - k)) );
	buff.blue	= static_cast<uint8_t>( (a.blue  * k) + (b.blue  * (1.0f - k)) );

	return buff;
}

rgb_t KolibriLib::Colors::UINT32toRGB(const uint32_t &color)
{
	rgb_t ret;
	
	ret.blue	= ((const Color&)color).blue;
	ret.red		= ((const Color&)color).red;
	ret.green	= ((const Color&)color).green;
	
	return ret;
}