#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/constants.hpp>
#include <kolibriLib/img.hpp>
#include <kolibriLib/system/filesystem/filesystem.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace KolibriLib
{
	namespace UI
	{
		/// @brief Работа с изображениями
		namespace Images
		{
			/// @brief Картинка как элемент интерфейса
			class Image : public UIElement, public img
			{				
			public:

				/// @brief Конструктор
				/// @param coord Координаты
				/// @param size Размер
				/// @param Path Путь до картинки
				/// @param Margin
				Image(const UDim& coord = point(0), const UDim& size = DefaultSize);

				/// @brief Конструктор копирования
				/// @param copy 
				Image(const Image &copy);

				/// @brief Вывести изображение в окно
				/// @param size Размер выводимого изображения
				void Render() const;

				/// @brief 
				/// @param a 
				/// @return 
				Image& operator = (const Image& a);

				void init(const Coord &coord = {0, 0}, const Size &size = {100, 100}, const filesystem::Path &Path = DefaultImage);
			};

		} // namespace Image

				

	} // namespace UI
	
} // namespace KolibriLib


#endif // __IMAGE_H__