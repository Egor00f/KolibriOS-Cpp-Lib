#include <kolibriLib/types.hpp>

using namespace KolibriLib;

KolibriLib::point::point(int X, int Y)
{
	x = X;
	y = Y;
}

KolibriLib::point::point(float f)
{
	x = f / 10.0;
	y = 10;

	if (x != y)
	{
		//====================================================
		int num = x, denom = y, rem;
		if (num < denom)
		{
			int temp = num;
			num = denom;
			denom = temp;
		}
		while (rem = num % denom)
		{
			num = denom;
			denom = rem;
		}
		//====================================================
		x /= rem;
		y /= rem;
	}
	else
	{
		x = 1;
		y = 1;
	}
}

ksys_pos_t KolibriLib::point::GetKsysPost() const
{
	ksys_pos_t buff;
	buff.x = x;
	buff.y = y;
	return buff;
}

point &KolibriLib::point::operator+(const point &a)
{
	x += a.x;
	y += a.y;
	return *this;
}

point &KolibriLib::point::operator-(const point &a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}

point &KolibriLib::point::operator=(const point &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

point &point::operator+=(const int &p)
{
	x += p;
	y += p;
	return *this;
}

point &point::operator-=(const int &p)
{
	x -= p;
	y -= p;
	return *this;
}

point &point::operator*=(const int &p)
{
	x *= p;
	y *= p;
	return *this;
}

point &point::operator/=(const int &p)
{
	x /= p;
	y /= p;
	return *this;
}

bool point::operator==(const point &a) const
{
	return x == a.x && y == a.y;
}

bool point::operator!=(const point &a) const
{
	return x != a.x || y != a.y;
}

