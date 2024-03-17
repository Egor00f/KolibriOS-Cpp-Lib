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

UI::Images::img::img()
{
	_img = img_create(32, 32, IMAGE_BPP32);
}

KolibriLib::UI::Images::img::img(Colors::Color *color, unsigned x, unsigned y)
{
	_img = img_create(x, y, IMAGE_BPP32);
	for(unsigned i = 0; i < x * y; i++)
	{
		*_img->Data = color[i].val;
	}
}

UI::Images::img::~img()
	
{
	img_destroy(_img);
}

void UI::Images::img::Render(const Coord &coord, const Size &size) const
{
	if(size.x != -1 || size.y != -1)
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

Colors::Color KolibriLib::UI::Images::img::GetPixel(unsigned x, unsigned y) const
{
	return _img->Data[x * _img->Width + y];
}

rgb_t *KolibriLib::UI::Images::img::GetRGBMap() const
{
	rgb_t * buff = new rgb_t[_img->Width * _img->Height];

	for(unsigned i = 0; i < _img->Width * _img->Height; i++)
	{
		buff[i] = Colors::UINT32toRGB(_img->Data[i]);
	}

	return buff;
}

Image_t* KolibriLib::UI::Images::img::GetImaget() const
{
	return _img;
}

void KolibriLib::UI::Images::img::FillColor(const Colors::Color &color)
{
	img_fill_color(_img, _img->Width, _img->Height, color.val);
}

bool KolibriLib::UI::Images::img::operator!=(const img &im) const
{
	if(_img->Width != im._img->Width || _img->Height != im._img->Height)
	{
		return true;
	}
	for(unsigned i = 0; i < _img->Width * _img->Height; i++)
	{
		if(_img->Data[i] != im._img->Data[i])
		{
			return true;
		}
	}
	return false;
}