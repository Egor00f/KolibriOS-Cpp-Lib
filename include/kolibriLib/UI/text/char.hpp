#ifndef __UI_CHAR_H__
#define __UI_CHAR_H__

#include <assert.h>
#include "textBase.hpp"
#include <kolibriLib/color.hpp>
#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/img.hpp>
#include "fontslist.hpp"

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
				typedef enum Type
				{
					None = 0,
					Image,
					Text
				};

				/// @brief Конструктор
				/// @param c символ
				/// @param size размеры символа
				/// @param flags флаги
				/// @param TextColor Цвет текста
				/// @param BackgroundColor Цвет фона
				Char(const char &c = ' ', const Fonts::Font &font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

				/// @brief Конструктор
				/// @param img изображение
				Char(const Images::img &img, const Fonts::Font &font = Fonts::DefaultFont);

				/// @brief Деструктор
				~Char();

				/// @brief Получить тип
				/// @return значение из списка Type
				Type GetType() const;

				/// @brief
				/// @param c
				/// @param size Размер символа
				/// @param flags Флаги из списка Flags
				/// @param TextColor
				/// @param BackgroundColor
				void Set(const char c, const Fonts::Font &font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

				/// @brief
				/// @param img
				void Set(const Images::Image &img, const Fonts::Font &size = Fonts::DefaultFont);

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

				/// @brief Получить _img
				/// @return
				const Images::img &GetImg() const;

				/// @brief получить размеры символа
				/// @return
				const Fonts::Font &GetFont() const;

				/// @brief Получить флаги
				/// @return
				unsigned GetFlags() const;

				/// @brief Отрисовать
				/// @param coord Координаты
				void Print(const Coord &coord) const;

				Char &operator=(char c);
				Char &operator=(const Images::img &img);
				Char &operator=(const Char &c);

				bool operator==(char c) const;
				bool operator==(const Images::img &img) const;
				bool operator==(const Char &img) const;
				bool operator!=(char c) const;
				bool operator!=(const Images::img &img) const;

			protected:
				Images::img *_img;
				char _c;

			private:
				/// @brief Освободить все переменные
				void Free();

				mutable Fonts::Font _font;

				/*====================Параметры для текста=================*/
				mutable Colors::Color *_TextColor;
				mutable Colors::Color *_BackgroundColor;
				/*=========================================================*/

				/// @brief Тип
				Type _type;
			};

		} // namespace text
		
	} // namespace UI
	
} // namespace KolibriLib


#endif // __UI_CHAR_H__