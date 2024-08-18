#include <kolibriLib/UI/text/freetype.hpp>
#include <kolibriLib/img.hpp>
#include <limits>
#include <algorithm>

using namespace FreeType;

Library _lib;

Library::Library()
{
	lib = 0;

	FT_Error err = FT_Init_FreeType(&lib);
	
	if(err)
	{
		KolibriLib::PrintDebug("Error init FreeType lib");
		throw err;
	}
}

FreeType::Library::~Library()
{
	FT_Error err = FT_Done_FreeType(lib);

	if(err)
	{
		throw err;
	}
}

FreeType::Library::operator FT_Library() const
{
	return lib;
}

FreeType::Face::Face(const char *file)
{
	face = 0;

	FT_Error err = FT_New_Face (
		_lib, 
		file, 
		0, 
		&face
	);

	if (err)
	{
		KolibriLib::PrintDebug("Error init FreeType face");
		throw err;
	}
}

FreeType::Face::operator FT_Face() const
{
	return face;
}

FT_Error FreeType::Face::SetCharSize(const KolibriLib::Size &NewCharSize)
{
	const KolibriLib::Size ScreenSize = KolibriLib::GetScreenSize();
	return FT_Set_Char_Size (
		face,
		NewCharSize.x*64,
		NewCharSize.y*64,
		ScreenSize.x,
		ScreenSize.y
	);
}

FT_Error FreeType::Face::SetCharSizePixels(const KolibriLib::Size &NewCharSize)
{
	return FT_Set_Pixel_Sizes (
		face,
		NewCharSize.x,
		NewCharSize.y
	);
}

FT_UInt FreeType::Face::GetGlyphIndex(const CharCode &charcode)
{
	return FT_Get_Char_Index(face, charcode);
}

FT_Error FreeType::Face::LoadGlyph(FT_UInt GlyphIndex, FT_Int LoadFlags)
{
	return FT_Load_Glyph(
		face,
		GlyphIndex,
		LoadFlags
	);
}

FT_Error FreeType::Face::LoadChar(const CharCode &charcode, FT_Int LoadFlags)
{
	return FT_Load_Char(face, charcode, LoadFlags);
}

FT_Error FreeType::Face::RenderGlyph(FT_Render_Mode RenderMode)
{
	return FT_Render_Glyph(face->glyph, RenderMode);
}

FT_Error FreeType::Face::SelectCharmap(FT_Encoding encoding)
{
	return FT_Select_Charmap(face, encoding);
}

void FreeType::Face::SetTransform(FT_Matrix *matrix, FT_Vector *delta)
{
	FT_Set_Transform(
		face, 
		matrix,
		delta
	);
}

FT_Vector Face::GetKerning(CharCode leftCharcode, CharCode rightCharcode, FT_Kerning_Mode KerningMode)
{
	FT_Vector delta;

	FT_Error err = FT_Get_Kerning(face, GetGlyphIndex(leftCharcode), GetGlyphIndex(rightCharcode), KerningMode, &delta);

	if(err)
		throw err;

	return delta;
}

FT_Glyph Face::GetGlyph()
{
	FT_Glyph ret;

	FT_Error err = FT_Get_Glyph(face->glyph, &ret);

	if(err)
		throw err;

	return ret;
}

void FreeType::DrawText(KolibriLib::Coord coord, const std::string text, Face face)
{
		int32_t left = std::numeric_limits<int>::max();
		int32_t top = std::numeric_limits<int>::max();
		int32_t bottom = std::numeric_limits<int>::min();

		CharCode PrevCharcode = 0;


		for(std::size_t i = 0; i < text.size(); i++)
		{
			const CharCode charcode = text[i];

			face.LoadChar(charcode);

			FT_GlyphSlot glyph = ((FT_Face)face)->glyph;

			if(!glyph)
				continue;

			if(PrevCharcode)		
			{
				coord.x += face.GetKerning(PrevCharcode, charcode).x;
			}
			PrevCharcode = charcode;

			coord.x += glyph->advance.x >> 10;

			auto bitmap = glyph->bitmap;

			//left = std::min(left, ((coord.x >> 6) + bitmap->left));
			//top = std::min(top, -bitmap->top);
			//bottom = std::max(bottom, -bitmap->top + bitmap->bitmap.rows);
			
			
			KolibriLib::UI::Images::img img(KolibriLib::Colors::Color(), {bitmap.width, bitmap.rows});


	
			for (int y = 0; y < bitmap.rows; y++)
			{
				for (int x = 0; x < bitmap.width; x++)
				{
					uint8_t r = bitmap.buffer[y * bitmap.pitch + x * 3];
					uint8_t g = bitmap.buffer[y * bitmap.pitch + x * 3 + 1];
					uint8_t b = bitmap.buffer[y * bitmap.pitch + x * 3 + 2];

					img.SetPixel(KolibriLib::Colors::Color(r, g, b), x, y);
				//img(col, row) = pixel{r, g, b, 255};
				// img and pixel are placeholders to simplify the code
				}
			}
			img.Draw(coord, {bitmap.width, bitmap.rows});
		}
	
}