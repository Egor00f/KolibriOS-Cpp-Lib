#ifndef __FREETYPE_HPP__
#define __FREETYPE_HPP__

#include <kolibriLib/types.hpp>
#include <kolibriLib/graphic/screen.hpp>
#include <kolibriLib/debug.hpp>
#include <stdint.h>
#include <vector>

/// @brief Библиотека freetype и оболочки для связки с KolibriLib
/// @details Зачем оболочки? Да чтоб просто не писать ручками FT_ТИП_New() и FT_ТИП_Done() и просто потому что могу
namespace FreeType
{
	#include <ft2build.h>
	#include FT_FREETYPE_H
	#include FT_GLYPH_H
	#include FT_TYPES_H
	#include FT_STROKER_H

	typedef FT_ULong CharCode;

	/// @brief Оболочка для FT_Error
	struct Error
	{
		FT_Error val;

		Error(FT_Error v = 0);

		Error& operator=(const  FT_Error& v);

		operator FT_Error() const;
		operator std::string() const;
		operator bool() const;
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

	/// @brief Оболочка для FT_Stroker
	class Stroker
	{
	public:
		Stroker();
		~Stroker();

		/// @brief 
		/// @param radius 
		/// @param cap 
		/// @param join 
		/// @param miterLimint 
		void Set(FT_Fixed radius, FT_Stroker_LineCap cap, FT_Stroker_LineJoin join, FT_Fixed miterLimint);

		void Rewind();

		operator FT_Stroker() const;

	private:
		FT_Stroker stroker;
	};

	/// @brief Оболочка для FT_Glyph
	class Glyph
	{
	public:

		/// @brief Конструктор поумолчанию
		Glyph():_glyph(0){}

		/// @brief Конструктор
		/// @param glyph глиф
		Glyph(FT_Glyph glyph);

		/// @brief Конструктор копирования
		Glyph(const Glyph &glyph);

		Error Stroke(Stroker stroker, FT_Bool destroy = false);

		Error StrokeBorder(Stroker stroker, FT_Bool inside, FT_Bool destroy = false);

		Error ToBitmap(FT_Render_Mode renderMode, FT_Vector *origin, FT_Bool destroy = false);

		FT_BitmapGlyph GetBitmapGlyph(FT_Render_Mode renderMode, FT_Vector *origin, FT_Bool destroy = false);

		Error Transform(FT_Matrix* matrix, FT_Vector* delta);

		/// @brief Копировать этот глиф
		Glyph Clone() const;

		operator FT_Glyph() const;

	private:
		FT_Glyph _glyph;
	};

	/// @brief Оболочка для FT_Face
	class Face
	{
	public:
		/// @brief Конструктор
		Face();

		/// @brief Конструктор
		/// @param file путь до файла
		/// @throw Если ошибка
		Face(const char* file);

		Face(const Face &c);

		/// @brief Деструктор
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

	void DrawText(const KolibriLib::Coord &coord, const std::string text, Face face);
} // namespace FreeType

namespace KolibriLib
{
	void PrintDebug(FreeType::Error out);
}

#endif // __FREETYPE_H__