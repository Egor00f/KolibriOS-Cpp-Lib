#include <kolibriLib/types.hpp>

using namespace KolibriLib;

KolibriLib::point::point(int X, int Y)
	: x(X), y(Y)
{
}

KolibriLib::point::point(const point & p)
	: x(p.x), y(p.y)
{
}

KolibriLib::point::point(const ksys_pos_t & pos)
	: x(pos.x), y(pos.y)
{
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

KolibriLib::point::operator ksys_pos_t() const
{
	return GetKsysPost();
}

KolibriLib::CoordA::CoordA(int X, int Y) 
	: point(X, Y), angle(0)
{
}

KolibriLib::CoordA::CoordA(int X, int Y, uint32_t A)
	: point(X, Y), angle(A)
{
}

CoordA &KolibriLib::CoordA::operator=(const point &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

bool KolibriLib::CoordA::operator==(const point &p) const
{
	return x == p.x &&
           y == p.y;
}

KolibriLib::CoordA::operator point() const
{
	return {x, y};
}

KolibriLib::CoordA::CoordA(const point &p)
	: point(p), angle(0)
{
}