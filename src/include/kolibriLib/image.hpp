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
			/// @brief Скопировать Image_t
			/// @param img Указатель на копируемую Image_t
			/// @return Указатель на копию
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
				void LoadImage(const filesystem::Path& Path);

				/// @brief Вывести изображение в окно
				/// @param size Размер выводимого изображения
				/// @paragraph Можно растянуть/сжать выводимое изображение введя новые размеры в переменную size, само изображение при этом не изменяется
				void Render(Size size = {0, 0});

				

				void init(const Coord &coord = {0, 0}, const Size &size = {100, 100}, const std::string &Path = DefaultImage);

				/// @brief Изменить изображение
				/// @param img Указатель на струтуру @link Image_t
				void SetImg(Image_t* img);
				
				Image& operator = (const Image& a)
				{
					_coord      = a._coord;
                    _size       = a._size;
                    _MainColor  = a._MainColor;
                    _Margin     = a._Margin;
					SetImg(a._img);

					return *this;
				}
			};

			Image_t *Copy(Image_t *img)
			{
				Image_t copy;

				copy.Checksum	= img->Checksum;
				copy.Data		= img->Data;
				copy.Delay		= img->Delay;
				copy.Extended	= img->Extended;
				copy.Flags		= img->Flags;
				copy.Height		= img->Height;
				copy.Next		= img->Next;
				copy.Palette	= img->Palette;
				copy.Previous	= img->Previous;
				copy.Type		= img->Type;
				copy.Width		= img->Width;

				Image_t *a = img_create(img->Width, img->Height, img->Type);

				*a = copy;

				return a;
			}

			Image::Image(const Coord &coord, const Size &size) : UIElement(coord, size)
			{
				#ifdef DEBUG == true
				_ksys_debug_puts("Image Constructor\n");
				#endif
			}

			Image::~Image()
			{
				img_destroy(_img);
			}

			void Image::LoadImage(const filesystem::Path &Path)
			{
				int32_t img_size;
				FILE *f = fopen(Path.GetChars(), "rb"); // Этот код взят из примера из /contrib/C_Layer/EXAMPLE/img_example/main.c

				if (!f)
				{
					char *a = "LoadImage: Can't open file: ";
					strcat(a, Path.GetChars());
					strcat(a, "\n");
					_ksys_debug_puts(a);
				}

				if (fseek(f, 0, SEEK_END))
				{
					char *a = "Can't SEEK_END file: ";
					strcat(a, Path.GetChars());
					strcat(a, "\n");
					_ksys_debug_puts(a);
				}

				int filesize = ftell(f);
				rewind(f);
				char *fdata = (char *)malloc(filesize);

				if (!fdata)
				{
					char *a = "No memory for file ";
					strcat(a, Path.GetChars());
					strcat(a, "\n");
					_ksys_debug_puts("malloc not return ptr");
				}

				img_size = (int32_t)fread(fdata, 1, filesize, f);

				if (ferror(f))
				{
					char *a = "Error reading file ";
					strcat(a, Path.GetChars());
					strcat(a, "\n");
					_ksys_debug_puts(a);
				}

				fclose(f);

				_img = img_decode((void *)fdata, img_size, 0);

				free(fdata);

				if (_img->Type != IMAGE_BPP32)
				{
					_img = img_convert(_img, NULL, IMAGE_BPP32, 0, 0); // Convert image to format BPP32
					if (!_img)
					{
						_ksys_debug_puts("Convert error");
					}
				}
			}

			void Image::Render(Size size)
			{
				if (size.x != 0 && size.y != 0)
				{
					Image_t *img = img_scale(_img, 0, 0, _size.x, _size.y, NULL, LIBIMG_SCALE_STRETCH, LIBIMG_INTER_BILINEAR, size.x, size.y);
					img_draw(img, _coord.x, _coord.y, size.x, size.y, 0, 0);
				}
				else
				{
					img_draw(_img, _coord.x, _coord.y, _size.x, _size.y, 0, 0);
				}
			}

			void Image::init(const Coord &coord, const Size &size, const std::string &Path)
			{
				_coord = coord;
				_size = size;
				LoadImage(Path);
			}

			void Image::SetImg(Image_t* img)
			{
				img_destroy(_img);
				_img = Copy(img);
			}
		} // namespace Image
	} // namespace UI
	
} // namespace KolibriLib


#endif // __IMAGE_H__