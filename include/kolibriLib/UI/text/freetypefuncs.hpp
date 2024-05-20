/**
 * \brief Набор функций, интегрированных с этой либой, для чуть большей простоты
*/
#ifndef __FREETYPEFUNCS_H__
#define __FREETYPEFUNCS_H__



#include <sys/ksys.h>
#include <cmath>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/globals.hpp>
#include <kolibriLib/img.hpp>



/// @brief Библиотека FreeType
/// @details Содержит библиотеку freetype и функции объёденяющие freetype и KoibriLib
namespace FreeType
{
	#include <ft2build.h>
	#include FT_FREETYPE_H
	#include FT_GLYPH_H

	/// @brief просто оболочка для FT_Library чтобы ручками не приходилось инициализировать
	struct FreeTypeLib
	{
		/// @brief Конструктор
		/// @throw генерирует исключение если прозошла ошибка
		FreeTypeLib();
		/// @brief
		/// @throw генерирует исключение если прозошла ошибка
		~FreeTypeLib();

		operator FT_Library() const;

		FT_Library _FreeType;
		bool loaded = false;
	};

	
	extern FreeTypeLib ft;


	/// @brief Отрисовать
	/// @param slot слот
	/// @param Coord координаты отрисовки
	/// @warning Вызывает page fault, хз почему
	void DrawBitmap(FT_Bitmap *bitmap,
					const FT_Int &x, const FT_Int &y,
					const KolibriLib::Coord &coord,
					const KolibriLib::Colors::Color &TextColor = KolibriLib::OS::GetSystemColors().gui_text,
					const KolibriLib::Colors::Color &BackgroundColor = KolibriLib::OS::GetSystemColors().win_body);

	/// @brief Отрисовать текст
	/// @param text текст
	/// @param face
	/// @param coord коорд
	/// @param loadFlags
	/// @return Ошибка
	FT_Error DrawText(const char *text, FT_Face face, const KolibriLib::CoordA &coord, uint32_t loadFlags = FT_LOAD_RENDER);

	/// @brief Загрузить FT_Face
	/// @param face face
	/// @param Path Путь до ttf файла
	/// @return Ошибка
	FT_Error LoadFace(FT_Face *face, const char *Path);

} // namespace FreeType

#endif // __FREETYPEFUNCS_H__