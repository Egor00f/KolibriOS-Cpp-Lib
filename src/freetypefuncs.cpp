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
	#ifdef DEBUG
	_ksys_debug_puts("DraText\n");
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
			return error;
		}
		DrawGlyphSlot(face->glyph, face->glyph->bitmap_left, face->glyph->bitmap_top, coord);
		pen.x += face->glyph->advance.x;
		pen.y += face->glyph->advance.y;
	}
}

void KolibriLib::DrawGlyphSlot(const FT_GlyphSlot &slot, FT_Int x, FT_Int y, const Coord &coord, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawGLyph\n");
	#endif
	FT_Int i, j, p, q;
	FT_Int x_max = x + slot->bitmap.width;
	FT_Int y_max = y + slot->bitmap.rows;

	const unsigned int RenderWidth = 128;
	const unsigned int RenderHeight = 128;

	Colors::Color *image = new Colors::Color[RenderWidth * RenderHeight];

	unsigned char um[RenderHeight][RenderWidth];

	for (i = x, p = 0; i < x_max; i++, p++)
	{
		for (j = y, q = 0; j < y_max; j++, q++)
		{
			if (i < 0 || j < 0 ||
				i >= RenderWidth || j >= RenderHeight)
				continue;

			um[j][i] |= slot->bitmap.buffer[q * slot->bitmap.width + p];
		}
	}

	for (i = 0; i < RenderHeight; i++)
	{
		for (j = 0; j < RenderWidth; j++)
		{
			if(um[i][j] != 0)
			{
				image[i * RenderHeight + j] = TextColor;
				image[i * RenderHeight + j]._a = um[i][j];
			}
			else
			{
				image[i * RenderHeight + j] = BackgroundColor;
			}
		}
	}



	ksys_draw_bitmap_palette(image,
							 coord.x,
							 coord.y,
							 RenderWidth,
							 RenderHeight,
							 32,
							 &slot->bitmap.palette,
							 0);
	
	delete[] image;
}