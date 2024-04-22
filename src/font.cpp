#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font::Font(const filesystem::Path &ttf_file)
{
	loadFontFromFile(ttf_file);
	SetSize({0, 32});
}

KolibriLib::UI::text::Fonts::Font::~Font()
{
	FT_Done_Face(_face);
}

void KolibriLib::UI::text::Fonts::Font::SetSize(const Size &size, const Size &dpi)
{
	_size = size;
	_dpi = dpi;
	FT_Set_Char_Size(_face, size.x * 64, 
                     size.y * 64, dpi.x, dpi.y);

}

FT_Error KolibriLib::UI::text::Fonts::Font::loadFontFromFile(const filesystem::Path &path)
{
	font_file = path;
	FT_Done_Face(_face);
	FT_Error error = LoadFace(&_face, path);
	
	switch (error)
	{
	case FT_Err_Ok:	//Если всё ок, то уходим
		break;
	case FT_Err_Unknown_File_Format:
		_ksys_debug_puts("Unknown font file format\n");
		break;
	case FT_Err_Corrupted_Font_Header:
		_ksys_debug_puts("Corrupted Font Header\n");
		break;
	case FT_Err_Invalid_Face_Handle:
		_ksys_debug_puts("invalid face handle\n");
		break;
	case FT_Err_Cannot_Open_Resource:
		_ksys_debug_puts("can't open resource\n");
	default:
		_ksys_debug_puts("Error load FT_Face\n");
		break;
	}

	return error;
}

KolibriLib::UI::text::Fonts::Font::Font(const Font *copy)
{
	loadFontFromFile(copy->font_file);
	SetSize(copy->_size, copy->_dpi);
}

UI::text::Fonts::Font& KolibriLib::UI::text::Fonts::Font::operator=(const Font &f)
{
	_size = f._size;
	_dpi = f._dpi;
	font_file = f.font_file;
	loadFontFromFile(font_file);
	return *this;
}

bool KolibriLib::UI::text::Fonts::Font::operator==(const Font &f) const
{
	return _size == f._size &&
		   _dpi == f._dpi &&
		   font_file == f.font_file;
}

bool KolibriLib::UI::text::Fonts::Font::operator!=(const Font &f) const
{
	return _size != f._size &&
	       _dpi != f._dpi &&
		   font_file != f.font_file;
}