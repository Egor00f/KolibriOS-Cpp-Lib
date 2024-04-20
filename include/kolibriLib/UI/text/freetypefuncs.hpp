/**
 * \brief Набор функций, интегрированных с этой либой, для чуть большей простоты
*/
#ifndef __FREETYPEFUNCS_H__
#define __FREETYPEFUNCS_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <kolibriLib/types.hpp>
#include <kolibriLib/globals.hpp>

#include <sys/ksys.h>

/// @brief Отрисовать глиф
/// @param slot слот
/// @param Coord координаты отрисовки
void DrawGlyphSlot(FT_GlyphSlot slot, KolibriLib::Coord coord)
{
	ksys_draw_bitmap_palette(&slot->bitmap.buffer,
							 coord.x + slot->bitmap_left,
							 coord.y + slot->bitmap_top,
							 slot->bitmap.width,
							 slot->bitmap.rows,
							 32,
							 &slot->bitmap.palette,
							 slot->bitmap.pitch);
}

inline FT_Error DrawText(const char *text, const FT_Face &face, KolibriLib::Coord coord, uint32_t loadFlags = FT_LOAD_RENDER)
{
	for (int i = 0; i < strlen(text); i++)
	{
		FT_Error error = FT_Load_Char(face, text[i], loadFlags);
		DrawGlyphSlot(face->glyph, coord);
		coord.x += face->glyph->advance.x >> 6;
	}
}

/// @brief Загрузить FT_Face
/// @param face face
/// @param Path Путь до ttf файла
/// @return Ошибка
inline static FT_Error LoadFace(FT_Face *face, const char *Path)
{
	return FT_New_Face(KolibriLib::Globals::_ft, Path, 0, face);
}

#endif // __FREETYPEFUNCS_H__