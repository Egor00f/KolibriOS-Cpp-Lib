#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font::Font(const char *ttf_file)
{
	if (loadFontFromTTF(ttf_file))
	{
		_ksys_debug_puts("failed load ttf file");
	}
}

void KolibriLib::UI::text::Fonts::Font::SetSize(const Size &size)
{
	_size = size;
	FT_Set_Pixel_Sizes(_face, size.x, size.y);
}

bool KolibriLib::UI::text::Fonts::Font::loadFontFromTTF(const char *path)
{
	return LoadFace(&_face, path);
}

void KolibriLib::UI::text::DrawText(const std::string & text, const Fonts::Font & font, Coord coord)
{
	for(int i = 0; i < text.length(); i++)
	{
		FT_Error error = FT_Load_Char(font._face, text[i], FT_LOAD_RENDER);
		DrawGlyphSlot(font._face->glyph, coord);
		coord.x += font._face->glyph->advance.x >> 6;
	}
}