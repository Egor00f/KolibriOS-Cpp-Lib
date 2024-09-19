#ifndef __TEXTBASE_HPP__
#define __TEXTBASE_HPP__

#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/globals.hpp>

// #include "font.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{
			/// \brief Получить размер текста
			/// \return текущая высота текста
			inline std::uint32_t GetTextSize()
			{
				std::uint32_t Size;

				asm_inline (
					"int $0x40"
					: "=c"(Size)
					: "a"(48), "b"(11));

				return Size;
			}

			/// \brief Изменить размер текста
			/// \param newSize высота текста в px
			inline void SetTextSize(std::uint8_t newSize)
			{
				asm_inline (
					"int $0x40" 
					:: 
					"a"(48), 
					"b"(12), 
					"c"(newSize));
			}

			/// \brief Просто вывести текст
			/// \param text текст
			/// \param coord координаты
			/// \param color цвет текста
			/// @note Для изменения высоты шрифта используйте SetTextSize()
			inline void DrawText(const std::string &text, const Coord &coord, std::uint8_t size = 9, const Colors::Color &color = Globals::SystemColors.work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color);
			}

			enum class TextEncoding
			{
				cp866_6x9 = 0,
				cp866_8x16 = 1,
				UTF16LE = 2,
				UTF8 = 3
			};

			/// @brief Вывести текст
			/// @param text текст
			/// @param coord координаты
			/// @param color цвет текста
			/// @param encoding кодировка, см. TextEncoding
			/// @param scale множитель размера(по умолчанию 1x), максимум 8x (0 = 1x, 7 = 8x)
			inline void DrawText(const std::string &text, const Coord &coord, Colors::Color color = Globals::SystemColors.work_text, TextEncoding encoding = TextEncoding::UTF8, std::uint8_t scale = 0)
			{
				color._a = static_cast<std::uint8_t>(static_cast<std::uint8_t>(encoding) << 4);
				color._a |= scale;
				asm_inline(
					"int $0x40" ::"a"(4),
					"b"(coord.operator ksys_pos_t()),
					"c"(color.val),
					"d"(text.c_str()),
					"S"(text.length()));
			}

			/// @brief Вывести текст
			/// @param text текст
			/// @param coord координаты
			/// @param BackgroundColor Цвет фона
			/// @param color цвет текста
			/// @param encoding кодировка, см. TextEncoding
			/// @param scale множитель размера(по умолчанию 1x), максимум 8x (0 = 1x, 7 = 8x)
			inline void DrawText(const std::string &text, const Coord &coord, Colors::Color BackgroundColor, Colors::Color color = Globals::SystemColors.work_text, TextEncoding encoding = TextEncoding::UTF8, std::uint8_t scale = 0)
			{
				color._a = static_cast<std::uint8_t>(static_cast<std::uint8_t>(encoding) << 4);
				color._a |= scale;
				color._a |= (true << 6);
				asm_inline(
					"int $0x40" ::"a"(4),
					"b"(coord.operator ksys_pos_t()),
					"c"(color.val),
					"d"(text.c_str()),
					"S"(text.length()),
					"D"(BackgroundColor.val));
			}
		}
	}
}

#endif // __TEXTBASE_H__