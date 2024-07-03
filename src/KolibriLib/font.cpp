#include <kolibriLib/UI/text/font.hpp>

using namespace KolibriLib;

KolibriLib::UI::text::Fonts::Font::Font(const filesystem::Path &ttf_file, const Size &size)
{
	loadFontFromFile(ttf_file);
	SetSize(size);
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

	FreeType::FT_Error error = FreeType::LoadFace(&_face, path);
	if(error == FreeType::FT_Err_Ok)
	{
		faceloaded = true;
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