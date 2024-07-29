#include <kolibriLib/types.hpp>

using namespace KolibriLib;

KolibriLib::point::point()
	: x(0), y(0)
{
}

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

KolibriLib::point::point(int Number)
	:  x(Number), y(Number)
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

bool KolibriLib::point::operator<(const point &obj) const
{
	return (x < obj.x) || (y < obj.y);
}

bool KolibriLib::point::operator>(const point &obj) const
{
	return (x > obj.x) || (y > obj.y);
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

KolibriLib::UDim::UDim(const point &p)
{
	X.Offset = p.x;
	Y.Offset = p.y;
}

KolibriLib::UDim::UDim(float XScale, int XOffset, float YScale, int YOffset)
	: X(XScale, XOffset), Y(YScale, YOffset)
{

}

KolibriLib::UDim::Axis::Axis(float scale, int offset)
	: Scale(scale), Offset(offset)
{

}

bool UDim::Axis::operator==(const UDim::Axis &axis) const
{
	return Scale == axis.Scale && Offset == axis.Offset;
}

bool UDim::Axis::operator!=(const UDim::Axis &axis) const
{
	return Scale != axis.Scale || Offset != axis.Offset;
}

point KolibriLib::UDim::GetAbsolute(const point &Parent) const
{
	return { static_cast<int>(static_cast<float>(Parent.x) * X.Scale) + X.Offset,
	         static_cast<int>(static_cast<float>(Parent.y) * Y.Scale) + Y.Offset };
}

bool KolibriLib::UDim::operator==(const UDim &obj) const
{
	return X == obj.X && Y == obj.Y;
}

bool KolibriLib::UDim::operator!=(const UDim &obj) const
{
	return X != obj.X || Y != obj.Y;
}