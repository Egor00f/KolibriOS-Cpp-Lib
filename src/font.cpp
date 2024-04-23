#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font::Font(const filesystem::Path &ttf_file)
{
	loadFontFromFile(ttf_file);
	SetSize({32, 0});
}

KolibriLib::UI::text::Fonts::Font::~Font()
{
	FreeType::FT_Done_Face(_face);
}

void KolibriLib::UI::text::Fonts::Font::SetSize(const Size &size)
{
	_size = size;
	FreeType::FT_Set_Pixel_Sizes(_face, _size.x, size.y);

}

FreeType::FT_Error KolibriLib::UI::text::Fonts::Font::loadFontFromFile(const filesystem::Path &path)
{
	font_file = path;

	if(faceloaded)
	{
		FT_Done_Face(_face);
	}
	
	FreeType::FT_Error error = LoadFace(&_face, path);
	
	switch (error)
	{
	case FreeType::FT_Err_Ok:	//Если всё ок, то уходим
		faceloaded = true;
		break;
	case FreeType::FT_Err_Unknown_File_Format:
		_ksys_debug_puts("Unknown font file format\n");
		break;
	case FreeType::FT_Err_Corrupted_Font_Header:
		_ksys_debug_puts("Corrupted Font Header\n");
		break;
	case FreeType::FT_Err_Invalid_Face_Handle:
		_ksys_debug_puts("invalid face handle\n");
		break;
	case FreeType::FT_Err_Cannot_Open_Resource:
		_ksys_debug_puts("can't open resource\n");
		break;
	default:
		_ksys_debug_puts("Error load FT_Face\n");
		_ksys_debug_puts(itoa(error, nullptr, 10));
		_ksys_debug_putc('\n');
		break;
	}

	return error;
}

KolibriLib::UI::text::Fonts::Font::Font(const Font *copy)
{
	loadFontFromFile(copy->font_file);
	SetSize(copy->_size);
}

UI::text::Fonts::Font& KolibriLib::UI::text::Fonts::Font::operator=(const Font &f)
{
	_size = f._size;
	font_file = f.font_file;
	loadFontFromFile(font_file);
	return *this;
}

bool KolibriLib::UI::text::Fonts::Font::operator==(const Font &f) const
{
	return _size == f._size &&
		   font_file == f.font_file;
}

bool KolibriLib::UI::text::Fonts::Font::operator!=(const Font &f) const
{
	return _size != f._size &&
		   font_file != f.font_file;
}