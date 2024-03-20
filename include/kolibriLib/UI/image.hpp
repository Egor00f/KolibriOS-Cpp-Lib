#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/constants.hpp>
#include <kolibriLib/img.hpp>
#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <kolibri_libimg.h>

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
			private:
				
			public:
				/// @brief Конструктор
				/// @param coord Координаты
				/// @param size Размер
				/// @param Path Путь до картинки
				/// @param Margin
				Image(const Coord& coord = {0, 0}, const Size& size = {100, 100});

				/// @brief Деструктор
				~Image();

				/// @brief Вывести изображение в окно
				/// @param size Размер выводимого изображения
				/// @paragraph Можно растянуть/сжать выводимое изображение введя новые размеры в переменную size, само изображение при этом не изменяется
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