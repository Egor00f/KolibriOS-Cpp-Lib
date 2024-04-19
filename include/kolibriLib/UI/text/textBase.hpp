#ifndef __TEXTBASE_H__
#define __TEXTBASE_H__

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibri_rasterworks.h>

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
			/// @note Для изменения высоты шрифта используйте SetTextSize()
			inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::GetSystemColors().work_text)
			{
				SetTextSize(size);
				_ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
			}
		}
	}
}

#endif // __TEXTBASE_H__