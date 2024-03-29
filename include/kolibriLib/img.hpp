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

namespace KolibriLib
{
	namespace UI
	{
		namespace Images
		{
			/// @brief Изображение
			class img
			{
			protected:
				Image_t *_img;

			public:
				img();

				/// @brief Конструктор
				/// @param color Массив цветов
				/// @param size размеры изображения
				img(Colors::Color *color, const Size &size);

				/// @brief Конструктор
				/// @param color цвет
				/// @param size размеры изображения
				/// @note Закрашивает изображение в цвет
				img(const Colors::Color &color, const Size &size);

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
				/// @param img Указатель на струтуру Image_t
				void SetImg(const Image_t *img);

				/// @brief Изменить цвет пикселя
				/// @param color
				/// @param x
				/// @param y
				void SetPixel(const Colors::Color &color, unsigned x, unsigned y);

				/// @brief Изменить цвет пикселя
				/// @param color новый цвет
				void SetPixel(const Colors::Color &color, Coord coord);

				/// @brief Получить цвет пикселя
				/// @param x координата пикселя по оси X
				/// @param y координата пикселя по оси Y
				/// @return Цвет
				Colors::Color GetPixel(unsigned x, unsigned y) const;
				
				/// @brief Получить цвет пикселя
				/// @param coord координаты пикселя
				/// @return Цвет
				Colors::Color GetPixel(Coord coord) const;

				/// @brief Получить изображение как массив Colors::Color
				/// @return Указатель на img::_img->Data
				Colors::Color *GetColorsMap() const;

				/// @brief получить массив rgb_t
				/// @return возврацается копия
				/// @note не забудьте удалить копию после использования!
				rgb_t *GetRGBMap() const;

				/// @brief Изменить изображение по изображению из rgb_t
				/// @param rgbmap 
				/// @param size размер rgbmap
				/// @note Теряется Alpha
				void SetRGBMap(const rgb_t* rgbmap, const Size &size);

				/// @brief
				/// @return
				Image_t *GetImaget() const;

				/// @brief Получить разрешение изображения
				/// @return 
				Size GetSize() const;

				/// @brief Заполнить изображение цветом
				/// @param color цвет
				void FillColor(const Colors::Color &color);
				
				img& operator = (const img& im);

				bool operator!=(const img &im) const;
			};


		} // namespace Images

	} // namespace UI
} // namespace KolibriLib


#endif // __IMG_H__