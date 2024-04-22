/*
всякие разные базовые типы
*/
#ifndef __TYPES_H__
#define __TYPES_H__

#include <sys/ksys.h>
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

		/// @brief 
		/// @param pos 
		point(const ksys_pos_t &pos);

		/// @brief Конструктор копирования
		/// @param p 
		point(const point &p);

		ksys_pos_t GetKsysPost() const;

		operator ksys_pos_t() const;

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
		
	/// @brief Координаты c углом
	struct CoordA: public point
	{
		CoordA(int X = 0, int Y = 0);
		CoordA(int X, int Y, uint32_t A);
		CoordA(const point& p);
		/// @brief Угол наклона
		uint32_t angle;
		CoordA& operator=(const point& p);
		bool operator==(const point& p) const;
		operator point() const;
	};

	//==================================================================================================

	
//==================================================================================================

} // namespace KolibriLib



#endif // __TYPES_H__