#ifndef __TEXTBASE_H__
#define __TEXTBASE_H__

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibri_rasterworks.h>
#include "fonts.hpp"
#include <kolibriLib/UI/fontslist.hpp>

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{
			/// \brief Получить размер текста
			/// \return текущая высота текста
			/// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
			inline unsigned int GetTextSize()
			{
				unsigned Size;
				asm_inline(
					"int $0x40"
					: "=c"(Size)
					: "a"(48), "b"(11));
				return Size;
			}

			/// \brief Изменить размер текста
			/// \param newSize высота текста в px
			/// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
			inline void SetTextSize(unsigned newSize)
			{
				asm_inline(
					"int $0x40" 
					::"a"(48), "b"(12), "c"(newSize)
				);
			}

			/// \brief Просто вывести текст
			/// \param text текст
			/// \param coord координаты
			/// \param color цвет текста
			/// @paragraph Для изменения высоты шрифта используйте @link SetTextSize(unsigned)
			inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::GetSystemColors().work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
			}
		

			/// @brief 
			/// @param text 
			/// @param font 
			/// @param margin 
			/// @param colorText 
			/// @param BackgroundColor 
			/// @return 
			Images::img& DrawTextToImg(const std::string& text, 
									   const Fonts::Font &font, 
									   unsigned margin, 
									   const Colors::Color &colorText, 
									   const Colors::Color &BackgroundColor);

			/// @brief Вывести текст
			/// @param text Текст
			/// @param coord Координаты
			/// @param font Шрифт
			/// @param margin Отступы границ фона от текста
			/// @param colorText цвет текста
			/// @param BackgroundColor цвет фона
			/// @paragraph Функция выводить используя библиотеку RasterWorks
			inline void DrawText(const std::string &text,
						  const Coord &coord, const Fonts::Font &font = Fonts::DefaultFont,
						  unsigned margin = UI::DefaultMargin,
						  const Colors::Color &colorText = OS::GetSystemColors().work_text,
						  const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area)
			{
				text::DrawTextToImg(text, font, margin, colorText, BackgroundColor).Render(coord, 
																						   {(margin * 2) + font.size.x, 
																						   (margin * 2) + (font.size.y * text.length())});
			}
			
		}
	}
}

#endif // __TEXTBASE_H__