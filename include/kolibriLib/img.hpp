#ifndef __IMG_H__
#define __IMG_H__

#include <kolibri_libimg.h>
#include <kolibriLib/types.hpp>
#include <kolibriLib/constants.hpp>

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
				/// @param color цвет
				/// @param x размер изображения по оси X
				/// @param y размер изображения по оси Y
				img(Colors::Color *color, unsigned x, unsigned y);

				~img();

				/// @brief Отрисовать изображение
				/// @param coord координаты
				/// @param size кастомный размер
				virtual void Render(const Coord &coord, const Size &size = {-1, -1}) const;

				/// @brief Загрузить изображение
				/// @param Path путь до файла
				void LoadImage(const filesystem::Path &Path = DefaultImage);

				/// @brief Изменить изображение
				/// @param img Указатель на струтуру @link Image_t
				void SetImg(Image_t *img);

				/// @brief Изменить цвет пикселя
				/// @param color
				/// @param x
				/// @param y
				void SetPixel(const Colors::Color &color, unsigned x, unsigned y);

				/// @brief Изменить цвет пикселя
				/// @param color
				void SetPixel(const Colors::Color &color, Coord coord);

				/// @brief Получить цвет пикселя
				/// @param x координата пикселя по оси X
				/// @param y координата пикселя по оси Y
				/// @return Цвет
				Colors::Color GetPixel(unsigned x, unsigned y) const;

				/// @brief
				/// @return
				Colors::Color *GetColorsMap() const;

				/// @brief получить массив rgb_t
				/// @return
				rgb_t *GetRGBMap() const;

				/// @brief
				/// @return
				Image_t *GetImaget() const;

				void FillColor(const Colors::Color &color);

				bool operator!=(const img &i) const;
			};
		} // namespace Images

	} // namespace UI
} // namespace KolibriLib


#endif // __IMG_H__