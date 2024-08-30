/*
всякие разные базовые типы
*/
#ifndef __TYPES_H__
#define __TYPES_H__

#include <sys/ksys.h>
#include <kolibriLib/system/filesystem.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/thread.hpp>
#include <kolibriLib/debug.hpp>

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

		/// @brief Конструктор по умолчанию
		/// @details координаты {0,0}
		point();

		/// @brief Конструктор
		/// @param X 
		/// @param Y 
		point(int X, int Y);

		/// @brief Конструктор
		/// @param Number 
		point(int Number);

		/// @brief Конструктор
		/// @param pos 
		point(const ksys_pos_t &pos);

		/// @brief Конструктор копирования
		/// @param p 
		point(const point &p);

		ksys_pos_t GetKsysPost() const;

		operator ksys_pos_t() const;

		/// @details прибавляет к x и y значения из a (к x прибавляется a.x, к y прибавляется a.y)
		point& operator+=(const point &a);

		/// @details уменьшает x и y на значения из a (из x вычитается a.x, из y вычитается a.y)
		point& operator-=(const point &a);

		point operator+(const point &a) const;
		point operator-(const point &a) const;

		/// @brief 
		/// @param p 
		/// @return 
		point &operator=(const point &p);

		/// @brief Прибавить к обоим кординатам значение
		/// @param p значение
		/// @return 
		point &operator+=(const int &p);

		/// @brief Вычесть из обоих кординат значение
		/// @param p значение
		/// @return
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

		bool operator < (const point &obj) const;
		bool operator > (const point &obj) const;
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

	/// @brief Координаты/Размеры для элементов UI
	struct UDim
	{
		/// @brief Ось
		struct Axis
		{
			/// @brief Относительно размера окна
			float Scale;

			/// @brief В пикселях
			int Offset;

			/// @brief Конструктор
			/// @param scale
			/// @param offset
			Axis(float scale = 0, int offset = 0);

			bool operator==(const Axis &axis) const;
			bool operator!=(const Axis &axis) const;
		};

		/// @brief Оси X и Y
		UDim::Axis X, Y;

		/// @brief Конструктор
		/// @param XScale
		/// @param XOffset
		/// @param YScale
		/// @param YOffset
		UDim(float XScale, int XOffset, float YScale, int YOffset);

		/// @brief Конструктор
		/// @param x смещение по x
		/// @param y смещение по y
		/// @details только смещение
		UDim(int x = 0, int y = 0);

		/// @brief Конструктор
		/// @param x
		/// @param y
		UDim(float x, float y);

		/// @brief Конструктор
		/// @details делает тоже самое что и UDim(int, int), только x и y берутся из точки
		/// @param p точка
		UDim(const point &p);

		/// @brief получить абсолютные значения(в пикселях) относительно окна
		/// @return
		point GetAbsolute(const point &Parent = {Thread::GetThreadInfo().winx_size, Thread::GetThreadInfo().winy_size}) const;

		bool operator==(const UDim &obj) const;
		bool operator!=(const UDim &obj) const;
	};

	void PrintDebug(const point &out);

	void PrintDebug(const UDim::Axis &out);

	void PrintDebug(const UDim &out);

//==================================================================================================

} // namespace KolibriLib



#endif // __TYPES_H__