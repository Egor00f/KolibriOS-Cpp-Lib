#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include <vector>
#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/globals.hpp>

#include "textBase.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{

			/**
			 * @brief Размер символа по умолчанию
			 */
			const Size DefaultCharSize = {16, 16};

			/// @brief Текст
			/// @details Просто текст с аттрибутами
			class Txt
			{
			public:
				/// @brief Конструктор
				Txt() = default;

				/// @brief Конструктор
				/// @param text
				Txt(const std::string &text, const Colors::Color &TextColor = Globals::SystemColors.work_text);

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
				void Print(const Coord &coord, const Colors::Color &BackgroundColor = Globals::SystemColors.work_area) const;

				/// @brief Изменить цвет текста для всех символов
				/// @param Color
				void SetTextColor(const Colors::Color &Color);

				/// @brief Получить цвет текста
				/// @return Цвет текста
				Colors::Color GetTextColor() const;

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

				/**
				 * @brief 
				 * @param NewTextCharSize 
				 */
				void SetTextSize(const Size &NewTextCharSize);

				/// @brief 
				/// @return 
				Size GetTextSize() const;

				Txt &operator=(const Txt &) = default;

				/// @brief
				/// @param txt
				/// @return
				bool operator==(const Txt &txt) const;

				/**
				 * @brief Оператор неравенства
				 * @param txt с чем сравнивать
				 * @return 
				 */
				bool operator != (const Txt& txt) const;

			protected:

				
				/**
				 * @brief Текст
				 */
				std::string _data;

			private:
				/// @brief Размер символа
				Size _CharSize = DefaultCharSize;

				/// @brief Цвет Текста
				Colors::Color _TextColor = Globals::SystemColors.work_text;

				/**
				 * @brief Цвет выделения текста
				 * @warning не реализованно
				 */
				Colors::Color *SelectColor;

				
				/**
				 * @brief Можно ли выделять этот текст
				 * @warning не реализованно
				 */
				bool Selecteable;

				bool Italic = false;
				bool Bold = false;
				bool UnderLine = false;
				bool StrikeThrough = false;
			};

		} // namespace text

	} // namespace UI

	void PrintDebug(const UI::text::Txt &out);
} // namespace KolibriLib


#endif // __TEXT_HPP__
