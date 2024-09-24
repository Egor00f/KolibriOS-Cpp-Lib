#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/constants.hpp>
#include <kolibriLib/img.hpp>
#include <kolibriLib/filesystem/filesystem.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>

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
				void Render() const override;

				/// @brief 
				/// @param a 
				/// @return
				Image &operator=(const Image &a) = default;

				void swap(Image &e);
			};

		} // namespace Image

				

	} // namespace UI
	
} // namespace KolibriLib


#endif // __IMAGE_HPP__