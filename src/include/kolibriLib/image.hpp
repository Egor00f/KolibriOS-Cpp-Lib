#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UI.hpp"
#include "small.hpp"
#include "filesystem.hpp"
#include "color.hpp"

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <kolibri_libimg.h>

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с изображениями
        namespace Images
        {
            /// @brief Картинка как элемент интерфейса
            class image : public UIElement
            {
            private:
                Image *_img;

            public:
                /// @brief Конструктор
                /// @param coord
                /// @param size
                /// @param Path Путь до картинки
                /// @param Margin
                image(point<int> coord = {0, 0}, Size size = {100, 100}, std::string Path = DefaultImage);
                ~image();

                /// @brief Загрузить изображение
                /// @param Path путь до файла
                void LoadImage(const std::string &Path);

                /// @brief Вывести изображение в окно
                /// @param size Размер выводимого изображения
                /// @paragraph Можно растянуть/сжать выводимое изображение введя новые размеры в переменную size, само изображение при этом не изменяется
                void Render(Size size = {0, 0});
            };

            image::image(point<int> coord, Size size, std::string Path) : UIElement(coord, size, 0, 0)
            {
                LoadImage(Path);
            }

            image::~image()
            {
            }

            void image::LoadImage(const std::string &Path)
            {
                int32_t img_size;
                FILE *f = fopen(Path.c_str(), "rb");
                if (!f)
                {
                }
                if (fseek(f, 0, SEEK_END))
                {
                }
                int filesize = ftell(f);
                rewind(f);
                char *fdata = (char *)malloc(filesize);
                if (!fdata)
                {
                }
                img_size = (int32_t)fread(fdata, 1, filesize, f);
                if (ferror(f))
                {
                }
                fclose(f);

                void *file_data = fdata;

                _img = img_decode(file_data, img_size, 0);

                if (_img->Type != IMAGE_BPP32)
                {
                    _img = img_convert(_img, NULL, IMAGE_BPP32, 0, 0); // Convert image to format BPP32
                    if (!_img)
                    {
                    }
                }
            }

            void image::Render(Size size)
            {
                if (size.x != 0 && size.y != 0)
                {
                    Image *img = img_scale(_img, 0, 0, _size.x, _size.y, NULL, LIBIMG_SCALE_STRETCH, LIBIMG_INTER_BILINEAR, size.x, size.y);
                    img_draw(img, _coord.x, _coord.y, size.x, size.y, 0, 0);
                }
                else
                {
                    img_draw(_img, _coord.x, _coord.y, _size.x, _size.y, 0, 0);
                }
            }

        } // namespace Image
    } // namespace UI
    
} // namespace KolibriLib


#endif // __IMAGE_H__