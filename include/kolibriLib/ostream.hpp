#ifndef __KOLIBRILIB_OSSTREAM_HPP__
#define __KOLIBRILIB_OSSTREAM_HPP__

#include <KolibriLib.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const KolibriLib::ButtonID& id)
{
	return os << id.value;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::point& p)
{
	return os << "X: " << p.x << " Y: " << p.y;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::UDim::Axis& p)
{
	return os << "Scale: " << p.Scale << " Offset: " << p.Offset;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::UDim& p)
{
	return os << "X: " << p.X << " Y: " << p.Y;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::Color& color)
{
	return os << "Color:"\
		<< "Red: " << color.red \
		<< " Green: " << color.green \
		<< " Blue: " << color.blue;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::UIElement& element)
{
	return os << "UIElement" << std::endl \
		<< "Coord: " << element.GetCoord() << std::endl \
		<< "Size: " << element.GetSize() << std::endl \
		<< "MainColor" << element.GetColor() << std::endl;
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::BaseButton& element)
{
	return os << "BaseButton" << std::endl << "ID: " << element.GetId();
}

std::ostream &operator<<(std::ostream &os, const KolibriLib::Button& element)
{
	return os << static_cast<KolibriLib::BaseButton>(element) << std::endl << static_cast<KolibriLib::UIElement>(element);
}

#endif // __KOLIBRILIB_OSSTREAM_HPP__