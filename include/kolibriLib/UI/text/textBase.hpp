#ifndef __TEXTBASE_H__
#define __TEXTBASE_H__

#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>

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
			inline void SetTextSize(uint8_t newSize)
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
			/// @note Для изменения высоты шрифта используйте SetTextSize()
			inline void DrawText(const std::string &text, const Coord &coord, unsigned size = 9, const Colors::Color &color = OS::GetSystemColors().work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color);
			}

			typedef enum TextEncoding
			{
				cp866_6x9 = 0,
				cp866_8x16 = 1,
				UTF16LE = 2,
				UTF8 = 3
			} TextEncoding;

			/// @brief Вывести текст
			/// @param text текст
			/// @param coord координаты
			/// @param color цвет текста
			/// @param encoding кодировка, см. TextEncoding
			/// @param scale множитель размера(по умолчанию 1x), максимум 8x (0 = 1x, 7 = 8x)
			inline void DrawText(const std::string &text, const Coord &coord, Colors::Color color = OS::GetSystemColors().work_text, TextEncoding encoding = TextEncoding::UTF8, uint8_t scale = 0)
			{
				color._a = encoding << 4;
				color._a |= scale;
				asm_inline(
					"int $0x40"
					::"a"(4), 
					"b"((ksys_pos_t)coord), 
					"c"(color.val), 
					"d"(text.c_str()),
					"S"(text.length())
				);
			}
		}
	}
}

#endif // __TEXTBASE_H__