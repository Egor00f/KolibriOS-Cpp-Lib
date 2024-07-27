#ifndef __TEXT_H__
#define __TEXT_H__

#include <vector>
#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/system/os.hpp>

#include "textBase.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{

			const Size DefaultCharSize = {16, 9};

			/// @brief Текст
			/// @details Фактически std::vector Char ов
			class Txt
			{
			public:
				/// @brief Конструктор
				Txt();

				/// @brief Конструктор
				/// @param text
				Txt(const std::string &text, const Colors::Color &TextColor = OS::GetSystemColors().gui_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().gui_face);

				/// @brief Конструктор копирования
				/// @param copy объект который будет копироваться
				Txt(const Txt &copy);


				/// @brief Добавить строку в конец
				/// @param txt строка
				void Add(const std::string &txt);


				/// @brief Вставить строку
				/// @param txt строка
				/// @param i номер
				void insert(const std::string &txt, int i);

				/// @brief Удалить Char из текста
				/// @param i Номер удаляемого Charа
				void Delete(int i);

				/// @brief Вывести текст
				/// @param coord Координаты(левый верхний угол) текста
				void Print(const Coord &coord) const;

				/*/// @brief Изменить шрифт символов
				/// @param FontSize
				/// @details Изменяет размер символов для всех символов
				void SetFont(const Fonts::Font &Font);*/

				/// @brief Изменить цвет текста для всех символов
				/// @param Color
				void SetTextColor(const Colors::Color &Color);

				/// @brief Получить цвет текста
				/// @return Цвет текста
				Colors::Color GetTextColor() const;

				/// @brief Изменить цвет фона для всех символов
				/// @param Color
				void SetBackgroundColor(const Colors::Color &Color);

				/// @brief Получить цвет фона
				/// @return Цвет фона
				Colors::Color GetBackgroundColor() const;

				/// @brief Получить текст
				/// @return
				std::string GetText() const;

				/// @brief Получить символ под номером i
				/// @param i номер
				/// @return _data.at(i)
				/// @throw std::string::at(std::size_t) можеть сгенерировать исключение
				char GetChar(std::size_t i) const;

				/// @brief Получить длину текста
				/// @return длина текста
				std::size_t length() const;

				/// @brief Получить длинну текста в пикселях
				/// @return
				unsigned lenghtPX() const;

				/// @brief Изменить текст
				/// @param text
				void SetText(const std::string &text);

				void SetTextSize(const Size &NewTextCharSize);

				/// @brief 
				/// @return 
				Size GetTextSize() const;

				Txt &operator=(const Txt &txt);

				/// @brief
				/// @param txt
				/// @return
				bool operator==(const Txt &txt) const;

			protected:
				std::string _data;

			private:
				/// @brief Размер символа
				Size _CharSize;

				/// @brief Цвет Текста
				Colors::Color _TextColor;

				/// @brief Цвет фона
				Colors::Color _BackgroundColor;

				/// @brief Цвет выделения текста
				Colors::Color *SelectColor;

				/// Можно ли выделять этот текст
				bool Selecteable;

				bool Italic;
				bool Bold;
				bool UnderLine;
				bool StrikeThrough;
			};

		} // namespace text

	} // namespace UI

} // namespace KolibriLib


#endif // __TEXT_H__
