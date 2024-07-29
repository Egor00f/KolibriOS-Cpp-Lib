#include <kolibriLib/color.hpp>

using namespace KolibriLib;
using namespace Colors;

KolibriLib::Colors::Color::Color(const ksys_color_t &a)
	: val(a)
{
}

KolibriLib::Colors::Color::Color(const KolibriLib::Colors::Color *a)
	: val(a->val)
{

}

KolibriLib::Colors::Color::Color(const KolibriLib::Colors::Color &a)
	: val(a.val)
{

}

KolibriLib::Colors::Color::Color(const rgb_t &color)
	: _a(0), red(color.red), green(color.green), blue(color.blue)
{

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

/*
KolibriLib::Colors::ColorsTable::ColorsTable(const ksys_colors_table_t &table)
{
	menu_body	= table.frame_area;
	gui_face	= table.grab_bar;
	btn_face	= table.work_button;
	btn_intext	= table.grab_button_text;
	gui_text	= table.grab_text;
	win_body	= table.work_area;
	btn_face	= table.work_button;
	btn_text	= table.work_button_text;
	gui_frame	= table.work_graph;
	btn_text	= table.work_text;
}

KolibriLib::Colors::ColorsTable::ColorsTable(const ColorsTable &table)
{	//Ужос
	btn_text	= table.btn_text;
	win_text	= table.win_text;
	panel_frame	= table.panel_frame;
	win_face	= table.win_face;
	win_inface	= table.win_inface;
	win_frame	= table.win_frame;
	win_inframe	= table.win_inframe;
	win_inborder	= table.win_inborder;
	win_graytext	= table.win_graytext;
	menu_frame	= table.menu_frame;
	menu_text	= table.menu_text;
	panel_body	= table.panel_body;
	panel_body	= table.panel_body;
	hint_frame	= table.hint_frame;
	hint_body	= table.hint_body;
	hint_text	= table.hint_text;
	btn_inface	= table.btn_inface;
	btn_fcface	= table.btn_fcface;
	btn_frame	= table.btn_frame;
	btn_inframe	= table.btn_inframe;
	btn_fcframe	= table.btn_fcframe;
	btn_intext	= table.btn_intext;
	btn_fctex	= table.btn_fctex;
	gui_shadow	= table.gui_shadow;
	gui_face	= table.gui_face;
	gui_inface	= table.gui_inface;
	gui_fcface	= table.gui_fcface;
	gui_frame	= table.gui_frame;
	gui_inframe	= table.gui_inframe;
	gui_fcframe	= table.gui_fcframe;
	gui_text	= table.gui_text;
	gui_intex	= table.gui_intex;
	gui_fctext	= table.gui_fctext;
	gui_select	= table.gui_select;
}
*/
ksys_color_t KolibriLib::Colors::RGBtoINT(const rgb_t &color)
{
	return ((color.red << 16) + (color.green << 8) + color.blue) & 0x00FFFFFF;
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
	ret.red 	= ((const Color&)color).red;
	ret.green	= ((const Color&)color).green;
	
	return ret;
}

KolibriLib::Colors::Color::operator rgb_t() const
{
	return GetRGB();
}

KolibriLib::Colors::Color::operator ksys_color_t() const
{
	return val;
}

void KolibriLib::PrintDebug(Colors::Color out)
{
    char buff[36];   // 23 символа в строке + 4 трехзначных числа(uint8_t)

    sprintf(buff, "Color: A: %X R: %X G: %X B: %X ", out._a, out.red, out.green, out.blue);

    DebugOut(buff);
}


void KolibriLib::PrintDebug(Colors::ColorsTable out)
{

    PrintDebug("ColorsTable:\n");

	Colors::Color* pointer = (Colors::Color*)&out;

    for (uint8_t i = 0; i < sizeof(Colors::ColorsTable) / sizeof(Colors::Color); i++)
    {
        PrintDebug((Colors::Color)pointer[i]);
        PrintDebug('\n');
    }

}