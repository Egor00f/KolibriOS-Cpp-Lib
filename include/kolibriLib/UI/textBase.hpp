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
			/// @note Для изменения высоты шрифта используйте @link SetTextSize(unsigned)
			inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::GetSystemColors().work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
			}
		

			/// @brief 
			/// @param text 
			/// @param font 
			/// @param margin 
			/// @param colorText цвет текста
			/// @param BackgroundColor цвет фона
			/// @return указатель на Images::img содержащие
			/// @note цвета фона и текста чувствительны к прозрачности
			/// @note прозрачность привязывается к контреным координатам и размерам
			Images::img* DrawTextToImg(const std::string& text, 
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
			/// @note Функция выводить используя библиотеку RasterWorks
			inline void DrawText(const std::string &text,
						  const Coord &coord, const Fonts::Font &font = Fonts::DefaultFont,
						  unsigned margin = UI::DefaultMargin,
						  const Colors::Color &colorText = OS::GetSystemColors().work_text,
						  const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area)
			{
				Images::img *buff = text::DrawTextToImg(text, font, margin, colorText, BackgroundColor);
				buff->Render(coord, Size((margin * 2) + font.size.x, (margin * 2) + (font.size.y * text.length())));
				delete buff;
			}
			
		}
	}
}

#endif // __TEXTBASE_H__