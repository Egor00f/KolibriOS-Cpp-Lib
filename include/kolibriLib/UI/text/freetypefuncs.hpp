/**
 * \brief Набор функций, интегрированных с этой либой, для чуть большей простоты
*/
#ifndef __FREETYPEFUNCS_H__
#define __FREETYPEFUNCS_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <sys/ksys.h>
#include <cmath>
#include <kolibriLib/globals.hpp>

/// @brief просто оболочка для FT_Library чтобы ручками не приходилось инициализировать
struct FreeTypeLib
{
	/// @brief Конструктор
	/// @throw генерирует исключение если прозошла ошибка
	FreeTypeLib();
	/// @brief
	/// @throw генерирует исключение если прозошла ошибка
	~FreeTypeLib();

	operator FT_Library();

	FT_Library _FreeType;
};

namespace KolibriLib
{
	namespace Globals
	{
		/// @brief А
		extern FreeTypeLib _ft;
	} // namespace Globals

	/// @brief Отрисовать глиф
	/// @param slot слот
	/// @param Coord координаты отрисовки
	void DrawGlyphSlot(const FT_GlyphSlot &slot, 
	                   FT_Int x, FT_Int y, 
					   const Coord &coord,
					    const Colors::Color &TextColor = OS::GetSystemColors().work_text, 
						const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

	/// @brief Отрисовать текст
	/// @param text текст
	/// @param face
	/// @param coord коорд
	/// @param loadFlags
	/// @return Ошибка
	FT_Error DrawText(const char *text, const FT_Face &face, const CoordA &coord, uint32_t loadFlags = FT_LOAD_RENDER);

	/// @brief Загрузить FT_Face
	/// @param face face
	/// @param Path Путь до ttf файла
	/// @return Ошибка
	inline FT_Error LoadFace(FT_Face *face, const char *Path)
	{
		return FT_New_Face(KolibriLib::Globals::_ft, Path, 0, face);
	}

} // namespace KolibriLib
#endif // __FREETYPEFUNCS_H__