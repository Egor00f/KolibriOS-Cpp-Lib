#include <kolibriLib/UI/image.hpp>

#include <kolibriLib/globals.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace Images;

Image::Image(const UDim &coord, const UDim &size)
	:	UIElement(coord, size), 
		img(Globals::SystemColors.work_graph, size.GetAbsolute({0,0}))
{
	PrintDebug("KolibriLib::UI::Images::Image Constructor");
}

KolibriLib::UI::Images::Image::Image(const Image & copy)
	:	UIElement(copy),
		img(copy)
{
	PrintDebug("KolibriLib::UI::Images::Image Constructor(copy)");
}

void KolibriLib::UI::Images::Image::Render() const
{
	Draw(GetAbsoluteCoord(), GetAbsoluteSize());
}

void KolibriLib::UI::Images::Image::swap(Image &e)
{
	Image buff(*this);

	*this = e;
	e = buff;
}

