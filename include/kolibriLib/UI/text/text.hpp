#ifndef __TEXT_H__
#define __TEXT_H__

#include <vector>
#include <string>

#include <kolibriLib/types.hpp>

#include "char.hpp"
#include "textBase.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{

			

			/// @brief Текст
			/// @note Фактически std::vector Char ов
			class Txt
			{
			public:
				/// @brief Конструктор
				Txt();

				/// @brief Конструктор
				/// @param text
				Txt(const std::string &text);

				/// @brief Конструктор копирования
				/// @param copy объект который будет копироваться
				Txt(const Txt &copy);

				/// @brief Добавить символ в конец
				/// @param c символ
				void Add(const Char &c);

				/// @brief Добавить строку в конец
				/// @param txt строка
				void Add(const std::string &txt);

				/// @brief долбавить изображение в конец
				/// @param img Добавляемое изображение
				void Add(const Images::img &img);

				/// @brief Вставить элемент
				/// @param c Символ
				/// @param i номер
				void insert(const Char &c, int i);

				/// @brief Вставить строку
				/// @param txt строка
				/// @param i номер
				void insert(const std::string &txt, int i);

				/// @brief Вставить изображение
				/// @param img изображение
				/// @param i номер
				void insert(const Images::img &img, int i);

				/// @brief Удалить Char из текста
				/// @param i Номер удаляемого Charа
				void Delete(int i);

				/// @brief Вывести текст
				/// @param coord Координаты(левый верхний угол) текста
				void Print(const Coord &coord) const;

				/// @brief Изменить шрифт символов
				/// @param FontSize
				/// @paragraph Изменяет размер символов для всех символов
				void SetFont(const Fonts::Font &Font);

				/// @brief Изменить цвет текста для всех символов
				/// @param Color
				void SetTextColor(const Colors::Color &Color);

				/// @brief Изменить цвет фона для всех символов
				/// @param Color
				void SetBackgroundColor(const Colors::Color &Color);

				/// @brief Получить текст
				/// @return
				std::string GetText() const;

				/// @brief Получить символ под номером i
				/// @param i номер
				/// @return _data[i]
				Char GetChar(int i) const;

				/// @brief Получить длину текста
				/// @return длина текста
				std::size_t length() const;

				/// @brief Получить длинну текста в пикселях
				/// @return
				unsigned lenghtPX() const;

				/// @brief Изменить текст
				/// @param text
				void SetText(const std::string &text);

				/// @brief Получить ширину текста
				/// @return ширина тектса в px
				unsigned GetWidth() const;

				Txt &operator=(const Txt &txt);

				/// @brief
				/// @param txt
				/// @return
				bool operator==(const Txt &txt) const;

			protected:
				Fonts::Font *_font;
				Colors::Color *_TextColor;
				std::vector<Char> _data;
			};

			
		} // namespace text
	} // namespace UI
} // namespace KolibriLib


#endif // __TEXT_H__