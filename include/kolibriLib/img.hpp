#ifndef __IMG_HPP__
#define __IMG_HPP__

#include <include_ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/constants.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/filesystem/filesystem.hpp>
#include <C_Layer/buf2d.hpp>

#include <string>
#include <memory>

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
				
				using BPP = buf2d::BPP;

				using RotateEnum = buf2d::RotateEnum;

				/**
				 * @brief Конструктор
				 * @param bpp Глубина цвета
				 */
				img(BPP bpp = BPP::RGB);

				/**
				 * @brief 
				 * @param size 
				 * @param bpp 
				 */
				img(const Size& size, BPP bpp = BPP::RGB);

				/**
				 * @brief 
				 * @param array 
				 * @param size 
				 */
				img(Colors::rgb* array, const Size& size);

				img(Colors::Color* array, const Size& size);

				/**
				 * @brief Конструктор 24-бит изображения
				 * @param color цвет
				 * @param size 
				 */
				img(const Colors::rgb& color, const Size& size);

				/**
				 * @brief Конструктор 32-бит
				 * @param color 
				 * @param size 
				 */
				img(const Colors::Color& color, const Size& size);

				/**
				 * @brief Констуктор копирования
				 * @param val 
				 * @details Полность копирует изображение
				 */
				img(const img& val);

				/**
				 * @brief 
				 */
				void Draw() const;

				/**
				 * @brief 
				 * @param coord 
				 */
				void Draw(const Coord& coord) const;

				/**
				 * @brief 
				 * @param coord 
				 * @param size 
				 */
				void Draw(const Coord& coord, const Size& size) const;

				/**
				 * @brief Изменить пиксель
				 * @param coord координаты пикселя
				 * @param color цвет
				 */
				void SetPixel(const Coord& coord,const Colors::Color& color);

				/**
				 * @brief Получить цвет пикселя
				 * @param coord координаты пикселя
				 * @return цвет пикселя
				 */
				Colors::Color GetPixel(const Coord& coord) const;

				/**
				 * @brief Получить глубину цвета
				 * @return 
				 */
				BPP GetBPP() const;

				/**
				 * @brief Повернуть изображение
				 * @param val 
				 */
				void Rotate(RotateEnum val);

				/**
				 * @brief 
				 * @param NewSize 
				 * @param resize 
				 */
				void Resize(const Size& NewSize, bool resize = true);

				/**
				 * @brief Получить размер изображения
				 * @return 
				 */
				Size GetSize() const;

				/**
				 * @brief Нарисовать круг
				 * @param coord координаты центра
				 * @param Radius радиус
				 * @param color цвет
				 */
				void DrawCircle(const Coord& coord, unsigned Radius, Colors::rgb color);

				/**
				 * @brief Нарисовать прямоугольник
				 * @param coord 
				 * @param size 
				 * @param color 
				 */
				void DrawRectangle(const Coord& coord, const Size& size, Colors::rgb color);

				/**
				 * @brief 
				 * @param coord 
				 * @param size 
				 * @param color 
				 */
				void DrawFilledRectangle(const Coord& coord, const Size& size, Colors::rgb color);

				/**
				 * @brief 
				 */
				void ResizeImgByX();

				/**
				 * @brief 
				 */
				void ResizeImgByY();

				/**
				 * @brief Прямая Безье
				 * @param points точки
				 * @param color цвет линии
				 */
				void CurveBezier(Coord points[3], Colors::Color color);

				/**
				 * @brief Оператор присваивания
				 * @param i 
				 * @return 
				 * @details Просто меняет указатель, если нужно скопировать изображение используйте конструктор копирования (img(const img&))
				 */
				img& operator=(const img& i);

				operator std::shared_ptr<buf2d_struct>() const;

			private:
				/**
				 * @brief Указатель на структуру для библиотеки buf2d
				 */
				std::shared_ptr<buf2d::buffer> _buff;
			};
		} // namespace Images
	} // namespace UI
} // namespace KolibriLib


#endif // __IMG_HPP__