#ifndef __UI_CHAR_H__
#define __UI_CHAR_H__

#include <assert.h>
#include "textBase.hpp"
#include <kolibriLib/color.hpp>
#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/img.hpp>
#include <kolibriLib/UI/text/font.hpp>
#include <kolibriLib/UI/text/fontslist.hpp>
#include <cstddef>
#include <cstring>

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{
			/// @brief Символ
			/// @note Символ который может содержать как текст, так и картинку(например смайлик)
			class Char
			{
			public:
				Char();

				/// @brief 
				/// @param c 
				/// @param font 
				/// @param TextColor 
				/// @param BackgroundColor
				Char(char c, const Fonts::Font &font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

				/// @brief Конструктор копирования
				/// @param copy 
				Char(const Char &copy);

				/// @brief Деструктор
				~Char();
				
				/// @brief Изменить флаги
				/// @param flags
				void SetFlags(unsigned flags);

				/// @brief Изменить цвет текста
				/// @param NewColor новый цвет фона
				void SetTextColor(const Colors::Color &NewColor);

				/// @brief Изменить цвет фона текста
				/// @param NewColor новый цвет фона
				void SetBackgroundColor(const Colors::Color &NewColor);

				/// @brief Измерить размеры символа
				/// @param size
				void SetFont(const Fonts::Font &size) const;

				/// @brief Получить ASCII символ
				/// @return
				char GetChar() const;

				/// @brief получить размеры символа
				/// @return
				const Fonts::Font GetFont() const;

				/// @brief Получить флаги
				/// @return
				unsigned GetFlags() const;

				/// @brief Отрисовать
				/// @param coord Координаты
				void Print(const Coord &coord) const;

				Char &operator=(char c);
				Char &operator=(const Char &c);

				bool operator==(char c) const;
				bool operator==(const Char &img) const;
				bool operator!=(char c) const;

			protected:
				char _c;

			private:				
				/// @brief Указатель на шрифт
				Fonts::Font *_font = nullptr;

				/// @brief
				Colors::Color *_TextColor = nullptr;

				/// @brief
				Colors::Color *_BackgroundColor = nullptr;
				
				bool ExternFont;
				bool ExternTextColor;
				bool ExternBackgroundColor;
			};

		} // namespace text
		
	} // namespace UI
	
} // namespace KolibriLib


#endif // __UI_CHAR_H__