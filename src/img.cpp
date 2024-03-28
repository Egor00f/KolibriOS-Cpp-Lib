#include <kolibriLib/img.hpp>


using namespace KolibriLib;
using namespace UI;
using namespace Images;

KolibriLib::UI::Images::img::img()
{
	_ksys_debug_puts("img consturctor\n");
	_img = img_create(32, 32, IMAGE_BPP32);
}

KolibriLib::UI::Images::img::img(Colors::Color *color, Size size)
{
	_ksys_debug_puts("img consturctor\n");
	_img = img_create(size.x, size.y, IMAGE_BPP32);
	for (unsigned i = 0; i < size.x * size.y; i++)
	{
		*_img->Data = color[i].val;
	}
}

KolibriLib::UI::Images::img::img(Colors::Color color, Size size)
{
	_ksys_debug_puts("img consturctor\n");
	img_fill_color(_img, size.x, size.y, color.val);
}

UI::Images::img::~img()
{
	img_destroy(_img);
}

void UI::Images::img::Render(const Coord &coord, const Size &size) const
{
	if (size.x != -1 || size.y != -1)
	{
		img_draw(_img, coord.x, coord.y, size.x, size.y, 0, 0);
	}
	else
	{
		img_draw(img_resize_data(_img, size.x, size.y), coord.x, coord.y, size.x, size.y, 0, 0);
	}
}

void UI::Images::img::SetImg(Image_t *img)
{
	img_destroy(_img);
	_img = img;
}

void KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, unsigned x, unsigned y)
{
	_img->Data[x * _img->Width + y] = color.val;
}

void KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, Coord coord)
{
	_img->Data[coord.x * _img->Width + coord.y] = color.val;
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(unsigned x, unsigned y) const
{
	return _img->Data[x * _img->Width + y];
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(Coord coord) const
{
	return _img->Data[coord.x * _img->Width + coord.y];
}

rgb_t *KolibriLib::UI::Images::img::GetRGBMap() const
{
	rgb_t *buff = new rgb_t[_img->Width * _img->Height];

	for (unsigned i = 0; i < _img->Width * _img->Height; i++)
	{
		buff[i] = Colors::UINT32toRGB(_img->Data[i]);
	}

	return buff;
}

Image_t *KolibriLib::UI::Images::img::GetImaget() const
{
	return _img;
}

void KolibriLib::UI::Images::img::FillColor(const Colors::Color &color)
{
	img_fill_color(_img, _img->Width, _img->Height, color.val);
}

KolibriLib::UI::Images::img& KolibriLib::UI::Images::img::operator = (const Images::img& im)
{
	if(_img->Width != im._img->Width || _img->Height != im._img->Height) //Если размеры картинок разные
	{
		img_resize_data(_img, im._img->Width, im._img->Height);
	}
	
	for(unsigned i = 0; i < _img->Width; i++)
	{
		for(unsigned j = 0; j < _img->Height; j++)
		{
			_img->Data[i * _img->Width + j] = im._img->Data[i * _img->Width + j];
		}
	}
	
	return *this;
}

bool KolibriLib::UI::Images::img::operator!=(const img &im) const
{
	if (_img->Width != im._img->Width || _img->Height != im._img->Height)
	{
		return true;
	}
	for (unsigned i = 0; i < _img->Width * _img->Height; i++)
	{
		if (_img->Data[i] != im._img->Data[i])
		{
			return true;
		}
	}
	return false;
}

Colors::Color *KolibriLib::UI::Images::img::GetColorsMap() const
{
	return (Colors::Color*)_img->Data;
}

Size img::GetSize() const
{
	return Size(_img->Width, _img->Height);
}

void img::LoadImage(const filesystem::Path &Path)
{
	_img = LoadImageFromFile(Path.GetChars());

	if (_img->Type != IMAGE_BPP32)
	{
		_img = img_convert(_img, NULL, IMAGE_BPP32, 0, 0); // Convert image to format BPP32
		if (!_img)
		{
			_ksys_debug_puts("Convert error");
		}
	}
}

void KolibriLib::UI::Images::img::SetRGBMap(const rgb_t *rgbmap, const Size &size)
{
	img_resize_data(_img, size.x, size.y);
	for(unsigned i = 0; i < size.x + size.y; i++)
	{
		_img->Data[i] = Colors::RGBtoINT(rgbmap[i]);
	}
}