#include <kolibriLib/UI/text/freetypefuncs.hpp>

FreeTypeLib::FreeTypeLib()
{
	FT_Error error = FT_Init_FreeType(&_FreeType);
	if (error)
	{
		throw error;
	}
}

FreeTypeLib::~FreeTypeLib()
{
	FT_Error error = FT_Done_FreeType(_FreeType);
	if(error)
	{
		throw error;
	}
}

FreeTypeLib::operator FT_Library()
{
	return _FreeType;
}

using namespace KolibriLib;

FreeTypeLib KolibriLib::Globals::_ft;

FT_Error KolibriLib::DrawText(const char *text, const FT_Face &face, const KolibriLib::CoordA &coord, uint32_t loadFlags)
{
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
		FT_Error error = FT_Load_Char(face,text[i], loadFlags);
		if(error != 0)
			return error;
		DrawGlyphSlot(face->glyph, face->glyph->bitmap_left, face->glyph->bitmap_top, coord);
		pen.x += face->glyph->advance.x;
		pen.y += face->glyph->advance.y;
	}
}

void KolibriLib::DrawGlyphSlot(const FT_GlyphSlot &slot, FT_Int x, FT_Int y, const Coord &coord)
{
	FT_Int i, j, p, q;
	FT_Int x_max = x + slot->bitmap.width;
	FT_Int y_max = y + slot->bitmap.rows;

	unsigned char *image = new unsigned char[480 * 640];

	for (i = x, p = 0; i < x_max; i++, p++)
	{
		for (j = y, q = 0; j < y_max; j++, q++)
		{
			if (i < 0 || j < 0 ||
				i >= 640 || j >= 480)
				continue;

			image[j * 480 + i] |= slot->bitmap.buffer[q * slot->bitmap.width + p];
		}
	}

	ksys_draw_bitmap_palette(image,
							 coord.x + slot->bitmap_left,
							 coord.y + slot->bitmap_top,
							 slot->bitmap.width,
							 slot->bitmap.rows,
							 32,
							 &slot->bitmap.palette,
							 slot->bitmap.pitch);
}