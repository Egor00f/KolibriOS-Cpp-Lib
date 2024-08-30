#ifndef __IMG_H__
#define __IMG_H__

#include <sys/ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/constants.hpp>

#include <string>

#include <C_Layer/INCLUDE/kolibri_buf2d.h>

namespace KolibriLib
{
	namespace UI
	{
		namespace Images
		{

			/// @brief Изображение
			class img
			{
			public:
				/// @brief Глубина цвета
				typedef enum
				{
					/// @brief  8 битный цвет
					bpp8 = 8,

					/// @brief 24 битный цвет
					RGB = 24,

					/// @brief 32 битный цвет
					RGBA = 32
				} imgBPP;

				typedef enum
				{
					rotate_90 = 90,
					rotate_180 = 180,
					rotate_270 = 1
				} RotateEnum;

				img(imgBPP bpp = imgBPP::RGB);

				/// @brief Конструктор
				/// @param color Массив цветов
				/// @param size размеры изображения
				img(const rgb_t *color, const Size &size, imgBPP bpp = imgBPP::RGB);

				/// @brief Конструктор
				/// @param color цвет
				/// @param size размеры изображения
				/// @note Закрашивает изображение в цвет
				img(const Colors::Color &color, const Size &size, imgBPP bpp = imgBPP::RGB);

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
				/// @return true если всё ок
				/// @return false если указаного пикселя не должно существовать
				bool SetPixel(const Colors::Color &color, unsigned x, unsigned y);

				/// @brief Изменить цвет пикселя
				/// @param color новый цвет
				/// @return true если всё ок
				/// @return false если указаного пикселя не должно существовать
				bool SetPixel(const Colors::Color &color, const Coord &coord);

				/// @brief Повернуть изображение на определённый угол
				/// @param value
				void Rotate(RotateEnum value);

				/// @brief Очистить изображение, 
				/// @param backgroundColor 
				void Clear(const Colors::Color &backgroundColor);

				/// @brief Нарисовать
				/// @param coord 
				/// @param radius 
				/// @param color 
				void DrawCircle(const Coord &coord, unsigned radius, const Colors::Color &color);

				/// @brief 
				/// @param point1 
				/// @param point2 
				/// @param color 
				void DrawLine(const Coord &point1, const Coord &point2, const Colors::Color &color);

				/// @brief 
				/// @param point1 
				/// @param point2 
				/// @param color 
				void DrawRectangle(const Coord &point1, const Coord &point2, const Colors::Color &color);

				/// @brief Получить цвет пикселя
				/// @param x координата пикселя по оси X
				/// @param y координата пикселя по оси Y
				/// @return Цвет
				Colors::Color GetPixel(unsigned x, unsigned y) const;
				
				/// @brief Получить цвет пикселя
				/// @param coord координаты пикселя
				/// @return Цвет
				Colors::Color GetPixel(const Coord &coord) const;

				/// @brief Получить изображение как массив цветов (Colors::Color)
				/// @return копия
				Colors::Color *GetColorsMap() const;

				/// @brief получить массив rgb_t
				/// @return возврацается копия
				/// @note не забудьте удалить копию после использования!
				rgb_t *GetRGBMap() const;

				/// @brief Изменить изображение по изображению из rgb_t
				/// @param rgbmap указатель на массив rgb_t
				/// @param size размер rgbmap, можно не указывать, но тогда размер буфера rgbmap должен соответсвовать размерам изображения
				/// @note Теряется Alpha
				void SetRGBMap(const rgb_t* rgbmap, const Size &size = {-1, -1});

				/// @brief Изменить изображение по изображению из цветов
				/// @param rgbmap указатель на массив Colors::Color
				/// @param size размер rgbmap, можно не указывать, но тогда размер буфера rgbmap должен соответсвовать размерам изображения
				/// @note Теряется Alpha
				void SetColorMap(const Colors::Color* rgbmap, const Size &size = {-1, -1});

				/// @brief Получить укзатель на img::_buff
				/// @return 
				buf2d_struct *GetBuff() const;

				/// @brief Получить разрешение изображения
				/// @return {img::_buff->width, img::_buff->height}
				Size GetSize() const;

				/// @brief Заполнить изображение цветом
				/// @param color цвет
				void FillColor(const Colors::Color &color);

				/// @brief Изменить кол-во бит на пиксель
				/// @param bpp кол-во бит на пиксель
				/// @param data дополнительные данные
				void SetBPP(imgBPP bpp, void *data);
				
				img& operator = (const img& im);
				bool operator == (const img &im) const;
				bool operator != (const img &im) const;

			private:
				buf2d_struct *_buff;
			};


		} // namespace Images

	} // namespace UI
} // namespace KolibriLib


#endif // __IMG_H__