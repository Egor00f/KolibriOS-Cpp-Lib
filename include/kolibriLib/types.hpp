/*
всякие разные базовые типы
*/
#ifndef __TYPES_H__
#define __TYPES_H__

#include <sys/ksys.h>
#include <kolibri_libimg.h>
#include <kolibriLib/constants.hpp>
#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/color.hpp>

#define X_Y(x, y)(((x) << 16) | (y))

namespace KolibriLib
{
	
	/// @brief Просто точка
	struct point
	{
		/// @brief координата по оси X, или ширина
		int x;
		/// @brief координата по оси Y, или высота
		int y;

		/// @brief Конструктор
		/// @param X 
		/// @param Y 
		point(int X = 0, int Y = 0);

		/// @brief Точка как отношение x/y
		/// @param f Десятичная дробь, которая ≈ x/y
		point(float f);

		ksys_pos_t GetKsysPost() const;

		point& operator+(const point &a);
		point &operator-(const point &a);

		/// @brief 
		/// @param p 
		/// @return 
		point &operator=(const point &p);

		/// @brief Прибавить к обоим кординатам значение
		/// @tparam B 
		/// @param p 
		/// @return 
		point &operator+=(const int &p);

		point &operator-=(const int &p);

		point &operator*=(const int &p);

		point &operator/=(const int &p);

		/// @brief 
		/// @param a 
		/// @return 
		bool operator==(const point &a) const;
		

		/// @brief 
		/// @param a 
		/// @return 
		bool operator!=(const point &a) const;
	};

	
	/// @brief Размер
	typedef point Size;
		
	/// @brief Координаты
	typedef point Coord;


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

				/// @brief
				/// @param color
				/// @param x размер изображения по оси X
				/// @param y размер изображения по оси Y
				img(Colors::Color * color, unsigned x, unsigned y);

				~img();

				/// @brief Отрисовать изображение
				/// @param coord координаты
				/// @param size кастомный размер
				virtual void Render(const Coord &coord, const Size &size = {-1,-1}) const;

				/// @brief Загрузить изображение
				/// @param Path путь до файла
				void LoadImage(const filesystem::Path &Path = DefaultImage);

				/// @brief Изменить изображение
				/// @param img Указатель на струтуру @link Image_t
				void SetImg(Image_t *img);

				/// @brief Изменить цвет пикселя
				/// @param color 
				void SetPixel(const Colors::Color &color, unsigned x, unsigned y);

				/// @brief Получить цвет пикселя
				/// @param x координата пикселя по оси X
				/// @param y координата пикселя по оси Y
				/// @return Цвет
				Colors::Color GetPixel(unsigned x, unsigned y) const;

				/// @brief 
				/// @return 
				Colors::Color* GetColorsMap() const;

				/// @brief получить массив rgb_t
				/// @return 
				rgb_t* GetRGBMap() const;

				/// @brief 
				/// @return 
				Image_t* GetImaget() const;

				void FillColor(const Colors::Color& color);

				bool operator != (const img& i) const;
			};
		} // namespace Images
		
	} // namespace UI
	

} // namespace KolibriLib



#endif // __TYPES_H__