#include <kolibriLib/UI/text/freetypefuncs.hpp>

using namespace FreeType;


FreeTypeLib::FreeTypeLib()
{
	FT_Error error = FT_Init_FreeType(&_FreeType);
	if (error)
		throw error;
	else
		loaded = true;
}

FreeTypeLib::~FreeTypeLib()
{
	if (loaded)						 // Если библитека была загружена
	{                                                //
		FT_Error error = FT_Done_FreeType(_FreeType);
		if (error)
		{
			throw error;
		}
	}
}

FreeTypeLib::operator FT_Library()
{
	return _FreeType;
}

FreeType::FreeTypeLib FreeType::ft;

FT_Error FreeType::DrawText(const char *text, const FT_Face &face, const KolibriLib::CoordA &coord, uint32_t loadFlags)
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawText\n");
	#endif
	FT_Matrix matrix;
	FT_Vector pen;
	double angle = (coord.angle / 360) * M_2_PI;

	pen.x = coord.x * 64;
	pen.y = coord.y * 64;

	matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
	matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
	matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
	matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

	for (int i = 0; i < strlen(text); i++)
	{
		FT_Set_Transform( face, &matrix, &pen );
		FT_Error error = FT_Load_Char(face, text[i], loadFlags);
		if(error != 0)
		{
			#ifdef DEBUG
			_ksys_debug_puts("Ret error\n");
			#endif
			//return error;
		}
		FreeType::DrawGlyphSlot(face->glyph, face->glyph->bitmap_left, face->glyph->bitmap_top, coord);
		pen.x += face->glyph->advance.x;
		pen.y += face->glyph->advance.y;
	}
}

void FreeType::DrawGlyphSlot(const FT_GlyphSlot &slot, FT_Int x, FT_Int y, const KolibriLib::Coord &coord, const KolibriLib::Colors::Color &TextColor, const KolibriLib::Colors::Color &BackgroundColor)
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawGLyph\n");
	#endif
	FT_Int RenderWidth = x + slot->bitmap.width;
	FT_Int RenderHeight = y + slot->bitmap.rows;


	KolibriLib::UI::Images::img image(BackgroundColor, {RenderWidth, RenderHeight}, KolibriLib::UI::Images::img::RGBA);

	_ksys_debug_puts("AA\n");

	for (int i = 0, k = y; i < RenderHeight && k < RenderHeight; i++, k++)
	{
		for ( int j = 0, l = x; j < RenderWidth && l < RenderWidth; j++, k++)
		{
			if(slot->bitmap.buffer[i * slot->bitmap.width + j] > 0)
			{
				KolibriLib::Colors::Color b(TextColor);
				b._a |= slot->bitmap.buffer[i * slot->bitmap.width + j];
				image.SetPixel(b, {k, l});	
			}
		}
	}
	
	image.Draw(coord);
}

FT_Error FreeType::LoadFace(FT_Face *face, const char *Path)
{
	return FT_New_Face(ft, Path, 0, face);
}