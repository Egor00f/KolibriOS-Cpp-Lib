#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UI.hpp"
#include "small.hpp"
#include "filesystem.hpp"
#include "color.hpp"

#include <string>
#include <stdlib.h>
#include <stdio.h>

extern "C"
{
#include "kolibri_libimg.h"
}
namespace KolibriLib
{
	namespace UI
	{
		/// @brief Работа с изображениями
		namespace Images
		{
			Image_t* Copy(Image_t *img);
			
			/// @brief Картинка как элемент интерфейса
			class Image : public UIElement
			{
			private:
				Image_t *_img;
			public:
				/// @brief Конструктор
				/// @param coord Координаты
				/// @param size Размер
				/// @param Path Путь до картинки
				/// @param Margin
				Image(const Coord& coord = {0, 0}, const Size& size = {100, 100});
				~Image();

				/// @brief Загрузить изображение
				/// @param Path путь до файла
				void LoadImage(const std::string &Path = DefaultImage);

				/// @brief Вывести изображение в окно
				/// @param size Размер выводимого изображения
				/// @paragraph Можно растянуть/сжать выводимое изображение введя новые размеры в переменную size, само изображение при этом не изменяется
				void Render(Size size = {0, 0});

				Image& operator = (const Image& a)
				{
					_coord      = a._coord;
                    _size       = a._size;
                    _MainColor  = a._MainColor;
                    _Margin     = a._Margin;
					

					return *this;
				}

				void init(const Coord &coord = {0, 0}, const Size &size = {100, 100}, const std::string &Path = DefaultImage);
			};


			
		} // namespace Image
	} // namespace UI
	
} // namespace KolibriLib


#endif // __IMAGE_H__