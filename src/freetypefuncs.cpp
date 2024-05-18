#include <kolibriLib/UI/text/freetypefuncs.hpp>

using namespace FreeType;

using KolibriLib::Coord;
using KolibriLib::Colors::Color;

FreeTypeLib::FreeTypeLib()
{
	FT_Error error = FT_Init_FreeType(&_FreeType);
	if (error != FT_Err_Ok)
		throw error;
	else
		loaded = true;
}

FreeTypeLib::~FreeTypeLib()
{
	if (loaded)						 // Если библитека была загружена
	{                                //
		FT_Error error = FT_Done_FreeType(_FreeType);
		if (error)
		{
			throw error;
		}
	}
}

FreeTypeLib::operator FT_Library() const
{
	return _FreeType;
}

FreeType::FreeTypeLib FreeType::ft;

FT_Error FreeType::DrawText(const char *text, FT_Face face, const KolibriLib::CoordA &coord, uint32_t loadFlags)
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawText\n");
	#endif
	FT_Matrix matrix;
	FT_Vector pen;
	FT_GlyphSlot slot = face->glyph;
	double angle = (coord.angle / 360) * M_2_PI;

	pen.x = coord.x * 64;
	pen.y = coord.y * 64;

	matrix.xx = (FT_Fixed)( cos(angle) * 0x10000L);
	matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
	matrix.yx = (FT_Fixed)( sin(angle) * 0x10000L);
	matrix.yy = (FT_Fixed)( cos(angle) * 0x10000L);

	int len = strlen(text);
	wchar_t *txt = (wchar_t*) malloc((len + 1) * sizeof(wchar_t));


	for (int i = 0; i < len; i++)
	{
		FT_Set_Transform( face, &matrix, &pen );
		FT_Error error = FT_Load_Char(face, txt[i], loadFlags);
		if(error != 0)
		{
			#ifdef DEBUG
			_ksys_debug_puts("Ret error\n");
			#endif
			//return error;
		}
		FreeType::DrawBitmap(&face->glyph->bitmap, face->glyph->bitmap_left, face->glyph->bitmap_top, coord);
		pen.x += face->glyph->advance.x;
		pen.y += face->glyph->advance.y;
	}
}

void FreeType::DrawBitmap(FT_Bitmap *bitmap, const FT_Int &x, const FT_Int &y, const KolibriLib::Coord &coord, const KolibriLib::Colors::Color &TextColor, const KolibriLib::Colors::Color &BackgroundColor)
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawGLyph\n");
	#endif
	const unsigned RenderWidth = 256;
	const unsigned RenderHeight = 256;
	FT_Int x_max = x + bitmap->width;
	FT_Int y_max = y + bitmap->rows;

	FT_Int i, j, p, q;

	KolibriLib::UI::Images::img image((const Color&)BackgroundColor, {RenderWidth, RenderHeight}, KolibriLib::UI::Images::img::RGBA);
	_ksys_debug_puts("AA\n");

	for (i = x, p = 0; i < x_max; i++, p++)
	{
		for (j = y, q = 0; j < y_max; j++, q++)

			if (i < 0 || j < 0 || i >= RenderWidth || j >= RenderHeight)
				continue;

			_ksys_debug_puts("continue\n");

			unsigned char buff = bitmap->buffer[q * bitmap->width + p];
		
			if(buff > 0)
			{
				_ksys_debug_puts("buf>0\n");
				KolibriLib::Colors::Color b(TextColor);
				b._a |= buff;
				image.SetPixel(b, {j, i});
				_ksys_debug_puts("done 1 cycle\n");	
			}
	}
	
	image.Draw(coord);
}

FT_Error FreeType::LoadFace(FT_Face *face, const char *Path)
{
	return FT_New_Face(ft, Path, 0, face);
}