#ifndef __RASTERWORKS_HPP__
#define __RASTERWORKS_HPP__

#include <C_Layer/INCLUDE/kolibri_rasterworks.h>
#include <kolibriLib/types.hpp>
#include <kolibriLib/globals.hpp>
#include <string>

#ifndef __MakeStaticLib__

class rasterwoksLib
{
public:
	rasterwoksLib()
	{
		if(kolibri_rasterworks_init() == -1)
			throw;
	}
};


rasterwoksLib rasterworksLibv;

#endif

/// @brief Оболочка для Сишной версии
/// @param canvas буффер, на котром будем рисовать
/// @param coord координаты текста в буфере
/// @param size размеры буфера
/// @param text текст
/// @param CharSize Размеры символов
/// @param FontColor цвет текста
/// @param flags флаги
/// @param encoding кодировка тектса
/// @return буффер
inline void *drawTextToBuff(const void *canvas, const KolibriLib::Coord &coord, const KolibriLib::Size &size, const std::string &text, const KolibriLib::Size &CharSize, const KolibriLib::Colors::Color &FontColor, const uint8_t &flags, const uint8_t encoding = RasterworksEncoding::Rasterworks_UTF8)
{
	return drawTextToBuff(
		canvas,
		static_cast<uint8_t>(size.x),
		static_cast<uint8_t>(size.y),
		coord.x,
		coord.y,
		text.c_str(),
		text.length(),
		static_cast<uint8_t>(CharSize.x),
		static_cast<uint8_t>(CharSize.y),
		FontColor.operator ksys_color_t(),
		static_cast<uint8_t>(flags),
		static_cast<uint8_t>(encoding));
}

/// @brief тоже что и drawTextToBuff, но сразу выводится текст
/// @param coord 
/// @param size 
/// @param text 
/// @param CharSize 
/// @param FontColor 
/// @param BackgroundColor 
/// @param flags 
/// @param encoding 
void drawtext(const KolibriLib::Coord &coord, const KolibriLib::Size &size, const std::string &text, const KolibriLib::Size &CharSize, const KolibriLib::Colors::Color &FontColor = KolibriLib::Globals::SystemColors.work_text, const KolibriLib::Colors::Color &BackgroundColor = KolibriLib::Globals::SystemColors.work_area, const uint8_t &flags = 0, const uint8_t encoding = RasterworksEncoding::Rasterworks_UTF8);

#endif // __RASTERWORKS_H__