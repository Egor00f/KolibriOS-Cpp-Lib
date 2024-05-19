#include <kolibriLib/UI/image.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace Images;

Image::Image(const UDim &coord, const UDim &size)
	: UIElement(coord, size), img(OS::GetSystemColors().work_graph, size.GetAbsolute())
{
	#ifdef DEBUG
	_ksys_debug_puts("KolibriLib::UI::Images::Image Constructor");
	#endif
}

KolibriLib::UI::Images::Image::Image(const Image & copy)
	:UIElement(copy._coord, copy._size, copy._MainColor, copy._Margin)
{
	#ifdef DEBUG
	_ksys_debug_puts("KolibriLib::UI::Images::Image Constructor(copy)");
	#endif
	SetImg(copy.GetBuff());
}

void Images::Image::init(const Coord &coord, const Size &size, const filesystem::Path &Path)
{
	_coord = coord;
	_size = size;
	LoadImage(Path);
}

void KolibriLib::UI::Images::Image::Render() const
{
	Draw(_coord.GetAbsolute(), _size.GetAbsolute());
}

Images::Image &KolibriLib::UI::Images::Image::operator=(const UI::Images::Image &a)
{
	_coord = a._coord;
	_size = a._size;
	_MainColor = a._MainColor;
	_Margin = a._Margin;
	SetImg(a.GetBuff());

	return *this;
}
