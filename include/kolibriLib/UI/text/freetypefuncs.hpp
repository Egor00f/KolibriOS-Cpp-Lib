/**
 * \brief Набор функций, интегрированных с этой либой, для чуть большей простоты
*/
#ifndef __FREETYPEFUNCS_H__
#define __FREETYPEFUNCS_H__

#include <sys/ksys.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TYPES_H
#include FT_GLYPH_H

#include <kolibriLib/types.hpp>
#include <kolibriLib/globals.hpp>


/// @brief Загрузить FT_Face
/// @param face &face
/// @param Path Путь до ttf файла
/// @return Ошибка
inline FT_Error LoadFace(FT_Face &face, const char *Path)
{
	return FT_New_Face(KolibriLib::Globals::_ft, Path, 0, &face);
}



/// @brief Отрисовать глиф
/// @param slot слот
/// @param Coord координаты отрисовки
/// @throw Генерирует исключение если кол-во бит на биксель битовой матрицы не поддерживается
void DrawGlyphSlot(const FT_GlyphSlot &slot, const KolibriLib::Coord &coord);


#endif // __FREETYPEFUNCS_H__