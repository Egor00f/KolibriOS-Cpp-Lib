#include <kolibriLib/img.hpp>

#include <C_Layer/INCLUDE/kolibri_libimg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace KolibriLib;
using namespace UI;
using namespace Images;

KolibriLib::UI::Images::img::img(img::BPP bpp)
{
	_buff = buf2d_create(0, 0, 32, 32, 0xFFFFFF, static_cast<std::uint8_t>(bpp));
}

KolibriLib::UI::Images::img::img(const Colors::Color &color, const Size &size, img::BPP bpp)
{
	_buff = buf2d_create(
		0, 
		0, 
		static_cast<unsigned int>(size.x), 
		static_cast<unsigned int>(size.y), 
		color.operator ksys_color_t(), 
		static_cast<std::uint8_t>(bpp)
	);
}

KolibriLib::UI::Images::img::img(const img & copy)
{
	// Я не знаю как там создаётся buf2d_struct, может просто malloc`а хватилобы, но я не уверен
	_buff = buf2d_create(copy._buff->left,
	                     copy._buff->top, 
						 copy._buff->width, 
						 copy._buff->height, 
						 copy._buff->bgcolor, 
						 copy._buff->color_bit);

	memcpy(&_buff->buf_pointer, &copy._buff->buf_pointer, copy._buff->width * copy._buff->height);
}

KolibriLib::UI::Images::img::img(const rgb_t *color, const Size &size, img::BPP bpp)
{
	this->_buff = buf2d_create(
		0, 
		0, 
		size.x, 
		size.y, 
		0xFFFFFF, 
		static_cast<std::uint8_t>(bpp));
	SetRGBMap(color, size);
}

/* Пока что его нет
KolibriLib::UI::Images::img::img(const filesystem::Path &ImageFile)
{
	Image_t *buff = LoadImageFromFile(ImageFile);

	//buf2d_create_f_img(this->_buff, buff->Data);

	img_destroy(buff);
}
*/

UI::Images::img::~img()
{
	buf2d_delete(this->_buff);
}

void UI::Images::img::Draw(const Coord &coord, const Size &size) const
{
	PrintDebug("DrawIMG");

	buf2d_struct *buff;

	_buff->left	= static_cast<uint16_t>(coord.x);
	_buff->top	= static_cast<uint16_t>(coord.y);

	// флаг того что буфер уже создан
	bool buffCreated = false;
	
	if(_buff->color_bit == 32)	// Если буфер 32-х битный
	{
		buff = buf2d_create(static_cast<uint16_t>(coord.x), static_cast<uint16_t>(coord.y), _buff->width, _buff->height, _buff->bgcolor, 24); // Создаётся буфер, создаётся только для того чтобы был
		buf2d_bit_blt_transp(buff, 0, 0, _buff);                                                // Применяется прозрачность
		buffCreated = true;                                                                     // буфер создан, поднять флаг
	}

	if(size != -1)
	{
		if(!buffCreated)                   // Если буфер не был создан ранее
		{                                  // То копируем _buff в buff
			buff = buf2d_copy(this->_buff);
		}

		buf2d_resize(
			buff, 
			static_cast<unsigned int>(size.x), 
			static_cast<unsigned int>(size.y), 
			BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize
		);
	}
	else
	{                 // Ничё с буфером делать не надо
		buff = _buff; 
	}

	buf2d_draw(buff);	// Наконец можно его вывести

	if(buffCreated)
	{
		buf2d_delete(buff);
	}
}

void UI::Images::img::SetImg(const buf2d_struct *img)
{
	this->_buff = buf2d_copy(img);
}

bool KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, unsigned x, unsigned y)
{
	if(x >= _buff->width || y >= _buff->height)
		return false;

	buf2d_set_pixel(this->_buff, x, y, color);
	return true;
}

bool KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, const Coord &coord)
{
	assert(coord.x >= _buff->width || coord.y >= _buff->height);
	
	
	buf2d_set_pixel(_buff, coord.y, coord.x, color);
	return true;
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(unsigned x, unsigned y) const
{
	assert(x >= _buff->width || y >= _buff->height);

	return buf2d_get_pixel(_buff, y, x);
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(const Coord &coord) const
{
	assert(coord.x >= _buff->width || coord.y >= _buff->height);

	return buf2d_get_pixel(_buff, static_cast<unsigned int>(coord.x), static_cast<unsigned int>(coord.y));
}

rgb_t *KolibriLib::UI::Images::img::GetRGBMap() const
{
	rgb_t *map = (rgb_t *) malloc(_buff->width * _buff->height * sizeof(rgb_t));

	switch(this->_buff->color_bit)
	{
		case 8:
			for (int i = 0; i < _buff->width * _buff->height; i++)
			{
				map[i].blue = ((uint8_t*)_buff->buf_pointer)[i];
			}
			break;

		case 24:

			for (int i = 0; i < _buff->width * _buff->height; i++)
			{
				map[i] = ((rgb_t*)_buff->buf_pointer)[i];
			}
			break;

		case 32:
			map = (rgb_t *)&buf2d_conv_32_to_24(_buff, NULL)->buf_pointer;
			break;

		default:
			return nullptr;
	}

	return map;
}

buf2d_struct *KolibriLib::UI::Images::img::GetBuff() const
{
	return this->_buff;
}

void KolibriLib::UI::Images::img::FillColor(const Colors::Color &color)
{
	buf2d_clear(this->_buff, color);
}

KolibriLib::UI::Images::img& KolibriLib::UI::Images::img::operator = (const Images::img& im)
{
	this->_buff = buf2d_copy(im._buff);
	
	return *this;
}

bool KolibriLib::UI::Images::img::operator!=(const img &im) const
{
	if (this->_buff->height != im._buff->height || this->_buff->width != im._buff->width) // если размеры изображний не совпадают то значит они точно не одинаковы
	{
		return true;
	}
	for (unsigned i = 0; i < this->_buff->width * this->_buff->height; i++)
	{
		if (this->_buff->buf_pointer[i] != im._buff->buf_pointer[i])
		{
			return true;
		}
	}
	return false;
}

Colors::Color *KolibriLib::UI::Images::img::GetColorsMap() const
{
	Colors::Color *buff = new Colors::Color[_buff->width * _buff->height];

	switch (_buff->color_bit)
	{
	case 32:
		for (int i = 0; i < _buff->width * _buff->height; i++)
		{
			buff[i] = Colors::Color((ksys_color_t)_buff->buf_pointer[i]);
		}
		break;
	case 24:
		for (int i = 0; i < _buff->width * _buff->height; i++)
		{
			buff[i] = Colors::Color(((rgb_t*)_buff->buf_pointer)[i]);
		}
		break;

	default:
		break;
	}

	return buff;
}

Size img::GetSize() const
{
	return Size(this->_buff->width, this->_buff->height);
}

void img::LoadImage(const filesystem::Path &Path)
{
	Image_t *buff = LoadImageFromFile(Path);

	if (buff->Type != IMAGE_BPP24)
	{
		buff = img_convert(buff, NULL, IMAGE_BPP24, 0, 0); // Convert image to format BPP24
		if (!buff)
		{
			PrintDebug("Convert error\n");
		}
	}

	img_to_rgb2(buff, this->_buff->buf_pointer);
}

void KolibriLib::UI::Images::img::SetRGBMap(const rgb_t *rgbmap, const Size &size)
{
	if (this->_buff->width != static_cast<unsigned>(size.x) && 
		this->_buff->height != static_cast<unsigned>(size.y)) // Если рамеры буфера не соответсвуют размерам rgbmap
	{													   // Изменяится размеры
		buf2d_resize (
			_buff, 
			static_cast<unsigned int>(size.x), 
			static_cast<unsigned int>(size.y), 
			BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize
		);
	}

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			buf2d_set_pixel(this->_buff, j, i, Colors::RGBtoINT(rgbmap[(i * size.x) + j]));
		}
	}
}

void KolibriLib::UI::Images::img::SetColorMap(const Colors::Color *rgbmap, const Size &size)
{
	if (size != -1 && this->_buff->width != size.x && this->_buff->height != size.y)	// Если рамеры буфера не соответсвуют размерам rgbmap
	{                                                                               	// Изменяится размеры
		buf2d_resize(this->_buff, size.x, size.y, BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize);
	}

	unsigned int* buff =(unsigned int*) malloc(size.x * size.y * sizeof(Colors::Color));
	memcpy(buff, rgbmap, size.x * size.y);
	free(_buff->buf_pointer);
	_buff->buf_pointer = buff;
}

bool KolibriLib::UI::Images::img::operator==(const img &im) const
{
	return _buff->color_bit	== im._buff->color_bit &&
	       im._buff->width	== _buff->width &&
           _buff->top	== im._buff->top &&
		   _buff->left	== im._buff->left &&
	       _buff->height	== im._buff->height;
}

void KolibriLib::UI::Images::img::SetBPP(img::BPP bpp, void *data)
{
	if (static_cast<std::uint8_t>(bpp) == _buff->color_bit)
	{
		return;
	}
	else if (bpp == img::BPP::RGB)
	{
		if(_buff->color_bit == static_cast<std::uint8_t>(img::BPP::RGBA))
		{
			
		}
		else if(_buff->color_bit == static_cast<std::uint8_t>(img::BPP::bpp8))
		{
			buf2d_conv_24_to_8(_buff, *(unsigned int*)data);
		}
	}
	else if (bpp == img::BPP::RGBA)
	{
		if (_buff->color_bit == static_cast<std::uint8_t>(img::BPP::RGB))
		{
			buf2d_struct* buff = buf2d_create(_buff->left, 
			                                 _buff->top, 
			                                 _buff->width, 
			                                 _buff->height, 
			                                 _buff->bgcolor,
			                                 24U);
			buf2d_conv_32_to_24(_buff, buff);
			buf2d_delete(_buff);
			_buff = buff;
		}
		else if(true)
		{

		}
	}
	else
	{

	}
}

void KolibriLib::UI::Images::img::Rotate(RotateEnum value)
{
	if(value == img::RotateEnum::rotate_270)
	{
		buf2d_rotate(_buff, 180);	//180+90=270
		buf2d_rotate(_buff, 90);
	}
	else
	{
		buf2d_rotate(_buff, static_cast<unsigned int>(value));
	}
}

void KolibriLib::UI::Images::img::Clear(const Colors::Color &backgroundColor)
{
	buf2d_clear(_buff, backgroundColor.operator ksys_color_t());
}

void KolibriLib::UI::Images::img::DrawCircle(const Coord &coord, unsigned radius, const Colors::Color &color)
{
	buf2d_circle(
		_buff, 
		static_cast<unsigned int>(coord.x), 
		static_cast<unsigned int>(coord.y), 
		radius,
		color.operator ksys_color_t());
}

void KolibriLib::UI::Images::img::Resize(const Size &NewSize)
{
	buf2d_resize(
		_buff,
		static_cast<unsigned int>(NewSize.x),
		static_cast<unsigned int>(NewSize.y),
		BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeImage);
}