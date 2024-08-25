#ifndef __FREETYPE_HPP__
#define __FREETYPE_HPP__

#include <kolibriLib/types.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/debug.hpp>
#include <stdint.h>
#include <vector>


/// @brief Библиотека freetype и оболочки для связки с KolibriLib
namespace FreeType
{
	#include <ft2build.h>
	#include FT_FREETYPE_H
	#include FT_GLYPH_H
	#include FT_TYPES_H

	typedef FT_ULong CharCode;

	struct Error
	{
		FT_Error val;

		Error(FT_Error v = 0);

		Error& operator=(const  FT_Error& v);

		operator FT_Error() const;
		operator std::string() const;
	};

	/// @brief Оболочка для FT_Libraty
	class Library
	{
	public:
		/// @brief Конструктор
		/// @throw Если ошибка
		Library();

		/// @brief Деструктор
		~Library();

		operator FT_Library() const;

	private:
		FT_Library lib;
	};

	/// @brief Оболочка для FT_Face
	class Face
	{
	public:
		/// @brief Конструктор
		Face():face(0){}

		/// @brief Конструктор
		/// @param file путь до файла
		/// @throw Если ошибка
		Face(const char* file);

		~Face();

		/// @brief Отурыть файл
		Error OpenFile(const char* filw);

		/// @brief Оболочка для FT_Set_Char_Size
		/// @param Новый размер сиволов
		/// @return Ошибка
		FT_Error SetCharSize(const KolibriLib::Size &NewCharSize);

		/// @brief Оболочка для FT_Set_Pixel_Sizes
		/// @param Новый размер сиволов в пикселях
		/// @return Ошибка
		FT_Error SetCharSizePixels(const KolibriLib::Size &NewCharSize);

		/// @brief Получить индекс глифа
		/// @param charcode 
		/// @return индекс
		FT_UInt GetGlyphIndex(const CharCode &charcode);

		/// @brief 
		/// @param GlyphIndex индекс
		/// @return 
		FT_Error LoadGlyph(FT_UInt GlyphIndex, FT_Int LoadFlags = FT_LOAD_DEFAULT);

		/// @brief 
		/// @param charcode 
		/// @return
		FT_Error LoadChar(const CharCode &charcode, FT_Int LoadFlags = FT_LOAD_DEFAULT);

		/// @brief 
		/// @param RenderMode 
		/// @return ошбка
		FT_Error RenderGlyph(FT_Render_Mode RenderMode = FT_RENDER_MODE_NORMAL);

		FT_Error SelectCharmap(FT_Encoding encoding);

		void SetTransform(FT_Matrix *matrix, FT_Vector *delta);

		/// @param leftCharcode код предыдущего символа
		/// @param rightCharcode код следующего символ
		/// @throw если ошибка
		FT_Vector GetKerning(CharCode leftCharcode, CharCode rightCharcode, FT_Kerning_Mode KerningMode = FT_KERNING_DEFAULT);

		/// @throw Если ошибка
		/// @return Глиф
		FT_Glyph GetGlyph();

		operator FT_Face() const;

	private:
		FT_Face face;
	};

	extern Library _lib;


	void DrawText(KolibriLib::Coord coord, const std::string text, Face face);
} // namespace FreeType

namespace KolibriLib
{
	void PrintDebug(FreeType::Error out);
}

#endif // __FREETYPE_H__