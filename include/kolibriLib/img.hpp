#ifndef __IMG_H__
#define __IMG_H__

#include <sys/ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/constants.hpp>

#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <kolibri_libimg.h>
#include <kolibri_buf2d.h>

namespace KolibriLib
{
	namespace UI
	{
		namespace Images
		{
			/// @brief Изображение
			class img
			{
			private:
				buf2d_struct *_buff;

			public:
				img();

				/// @brief Конструктор
				/// @param color Массив цветов
				/// @param size размеры изображения
				img(const rgb_t *color, const Size &size);

				/// @brief Конструктор
				/// @param color Массив цветов
				/// @param size размеры изображения
				img(const Colors::Color *color, const Size &size);

				/// @brief Конструктор
				/// @param color цвет
				/// @param size размеры изображения
				/// @note Закрашивает изображение в цвет
				img(const Colors::Color &color, const Size &size);

				img(const filesystem::Path &ImageFile);

				/// @brief Коструктор копирования
				/// @param copy то что будет копироваться
				img(const img &copy);

				/// @brief Деструктор
				~img();

				/// @brief Отрисовать изображение
				/// @param coord координаты
				/// @param size кастомный размер
				void Draw(const Coord &coord, const Size &size = {-1, -1}) const;

				/// @brief Загрузить изображение
				/// @param Path путь до файла
				void LoadImage(const filesystem::Path &Path = DefaultImage);

				/// @brief Изменить изображение
				/// @param img Указатель на струтуру
				void SetImg(const buf2d_struct *img);

				/// @brief Изменить цвет пикселя
				/// @param color
				/// @param x
				/// @param y
				void SetPixel(const Colors::Color &color, unsigned x, unsigned y);

				/// @brief Изменить цвет пикселя
				/// @param color новый цвет
				void SetPixel(const Colors::Color &color, const Coord &coord);

				void Rotate(int value);

				/// @brief Получить цвет пикселя
				/// @param x координата пикселя по оси X
				/// @param y координата пикселя по оси Y
				/// @return Цвет
				Colors::Color GetPixel(unsigned x, unsigned y) const;
				
				/// @brief Получить цвет пикселя
				/// @param coord координаты пикселя
				/// @return Цвет
				Colors::Color GetPixel(const Coord &coord) const;

				/// @brief Получить изображение как массив Colors::Color
				/// @return Указатель на img::_img->Data
				Colors::Color *GetColorsMap() const;

				/// @brief получить массив rgb_t
				/// @return возврацается копия
				/// @note не забудьте удалить копию после использования!
				rgb_t *GetRGBMap() const;

				/// @brief Изменить изображение по изображению из rgb_t
				/// @param rgbmap 
				/// @param size размер rgbmap, можно не указывать, но размер буфера rgbmap должен соответсвовать размерам изображения
				/// @note Теряется Alpha
				void SetRGBMap(const rgb_t* rgbmap, const Size &size = {-1, -1});

				void SetColorMap(const Colors::Color* rgbmap, const Size &size = {-1, -1});

				/// @brief
				/// @return
				buf2d_struct *GetBuff() const;

				/// @brief Получить разрешение изображения
				/// @return 
				Size GetSize() const;

				/// @brief Заполнить изображение цветом
				/// @param color цвет
				void FillColor(const Colors::Color &color);
				
				img& operator = (const img& im);
				bool operator==(const img &im) const;
				bool operator!=(const img &im) const;
			};


		} // namespace Images

	} // namespace UI
} // namespace KolibriLib


#endif // __IMG_H__