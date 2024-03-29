#include <kolibriLib/UI/image.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace Images;

Image::Image(const Coord &coord, const Size &size) : UIElement(coord, size), img(OS::GetSystemColors().work_graph, size)
{
	_ksys_debug_puts("KolibriLib::UI::Images::Image Constructor");
}

void Images::Image::init(const Coord &coord, const Size &size, const filesystem::Path &Path)
{
	_coord = coord;
	_size = size;
	LoadImage(Path);
}

void KolibriLib::UI::Images::Image::Render() const
{
	img_draw(_img, _coord.x, _coord.y, _size.x, _size.y, 0, 0);
}

Images::Image &KolibriLib::UI::Images::Image::operator=(const UI::Images::Image &a)
{
	_coord = a._coord;
	_size = a._size;
	_MainColor = a._MainColor;
	_Margin = a._Margin;
	SetImg(a._img);

	return *this;
}
