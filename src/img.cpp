#include <kolibriLib/img.hpp>


using namespace KolibriLib;
using namespace UI;
using namespace Images;

KolibriLib::UI::Images::img::img()
{
	#ifdef DEBUG
	_ksys_debug_puts("img consturctor(empety)\n");
	#endif

	_img = img_create(32, 32, IMAGE_BPP32);
}

KolibriLib::UI::Images::img::img(Colors::Color *color, const Size &size)
{
	#ifdef DEBUG
	_ksys_debug_puts("img consturctor\n");
	#endif

	_img = img_create(size.x, size.y, IMAGE_BPP32);
	for (unsigned i = 0; i < size.x * size.y; i++)
	{
		*_img->Data = color[i].val;
	}
}

KolibriLib::UI::Images::img::img(const Colors::Color &color, const Size &size)
{
	#ifdef DEBUG
	_ksys_debug_puts("img consturctor\n");
	#endif


	_img = img_create(size.x, size.y, IMAGE_BPP32);
	img_fill_color(_img, size.x, size.y, color.val);
}

KolibriLib::UI::Images::img::img(const img & copy)
{
	#ifdef DEBUG
	_ksys_debug_puts("img consturctor(copy)\n");
	#endif

	_img = img_Copy(copy._img);
}

UI::Images::img::~img()
{
	img_destroy(_img);
}

void UI::Images::img::Draw(const Coord &coord, const Size &size) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Draw img size:");
	_ksys_debug_puts(__itoa(size.x, nullptr, 10));
	_ksys_debug_putc(' ');
	_ksys_debug_puts(__itoa(size.y, nullptr, 10));
	_ksys_debug_putc('\n');
	#endif

	if ((size.x != -1 && size.y != -1) || (size.x == _img->Width && size.y == _img->Height))
	{
		img_draw(_img, coord.x, coord.y, size.x, size.y, 0, 0);
	}
	else
	{
		img_draw(img_resize_data(_img, size.x, size.y), coord.x, coord.y, size.x, size.y, 0, 0);
	}
}

void UI::Images::img::SetImg(const Image_t *img)
{
	img_destroy(_img);
	_img = img_Copy(img);
}

void KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, unsigned x, unsigned y)
{
	_img->Data[(y-1) * _img->Width + x] = color.val;
}

void KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, Coord coord)
{
	_img->Data[(coord.y-1) * _img->Width + coord.x] = color.val;
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(unsigned x, unsigned y) const
{
	return _img->Data[(y - 1) * _img->Width + x];
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(Coord coord) const
{
	return _img->Data[(coord.y - 1) * _img->Width + coord.x];
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
	if (_img->Width != im._img->Width || _img->Height != im._img->Height) // Если размеры картинок разные
	{
		img_resize_data(_img, im._img->Width, im._img->Height);
	}

	for (unsigned i = 0; i < _img->Width * _img->Height; i++)
	{
		_img->Data[i] = im._img->Data[i];
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