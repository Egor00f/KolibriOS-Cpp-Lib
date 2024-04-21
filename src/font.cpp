#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font::Font(const char *ttf_file)
{
	loadFontFromTTF(ttf_file);
	SetSize({32, 0}, {100, 0});
}

KolibriLib::UI::text::Fonts::Font::~Font()
{
	FT_Done_Face(_face);
}

void KolibriLib::UI::text::Fonts::Font::SetSize(const Size &size, const Size &dpi)
{
	_size = size;
	FT_Set_Char_Size(_face, size.x * 64, 
                     size.y, dpi.x, dpi.y);
}

FT_Error KolibriLib::UI::text::Fonts::Font::loadFontFromTTF(const char *path)
{
	FT_Error error = LoadFace(&_face, path);
	
	switch (error)
	{
	case FT_Err_Unknown_File_Format:
		_ksys_debug_puts("Unklown font file format\n");
		break;
	default:
		break;
	}

	return error;
}

KolibriLib::UI::text::Fonts::Font::Font(const Font * copy)
	: _face(copy->_face), _size(copy->_size)
{
}