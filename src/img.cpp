#include <kolibriLib/img.hpp>


using namespace KolibriLib;
using namespace UI;
using namespace Images;

KolibriLib::UI::Images::img::img(imgBPP bpp)
{
	this->_buff = buf2d_create(0,0, 32, 32, 0xFFFFFF, bpp);
}

KolibriLib::UI::Images::img::img(const Colors::Color *color, const Size &size, imgBPP bpp)
{
	this->_buff = buf2d_create(0, 0, size.x, size.y, 0xFFFFFF, bpp);
	SetColorMap(color, size);
}

KolibriLib::UI::Images::img::img(const Colors::Color &color, const Size &size, imgBPP bpp)
{
	_buff = buf2d_create(0, 0, size.x, size.y, color.val, bpp);
}

KolibriLib::UI::Images::img::img(const img & copy)
{
	_buff = buf2d_create(copy._buff->left,
	                     copy._buff->top, 
						 copy._buff->width, 
						 copy._buff->height, 
						 copy._buff->bgcolor, 
						 copy._buff->color_bit);

	memcpy(_buff->buf_pointer, copy._buff->buf_pointer, copy._buff->width * copy._buff->height);
}

KolibriLib::UI::Images::img::img(const rgb_t *color, const Size &size, imgBPP bpp)
{
	this->_buff = buf2d_create(0, 0, size.x, size.y, 0xFFFFFF, bpp);
	SetRGBMap(color, size);
}

KolibriLib::UI::Images::img::img(const filesystem::Path &ImageFile, imgBPP bpp)
{
	Image_t *buff = new Image_t;
	buff = LoadImageFromFile(ImageFile);

	buf2d_create_f_img(this->_buff, buff->Data);

	img_destroy(buff);
}

UI::Images::img::~img()
{

	buf2d_delete(this->_buff);
}

void UI::Images::img::Draw(const Coord &coord, const Size &size) const
{
	#ifdef DEBUG
	_ksys_debug_puts("DrawIMG\n");
	#endif

	buf2d_struct *buff;

	_buff->left = coord.x;
	_buff->top = coord.y;

	// флаг того что буфер уже создан
	bool buffCreated = false;
	
	if(_buff->color_bit == 32)
	{
		buff = buf2d_create(coord.x, coord.y, _buff->width, _buff->height, _buff->bgcolor, 24); // Создаётся буфер, создаётся только для того чтобы был
		buf2d_bit_blt_transp(buff, 0, 0, _buff);                                                // Применяется прозрачность
		buffCreated = true;                                                                     // буфер создан, поднять флаг
	}

	if(size != -1)
	{
		if(!buffCreated)                   // Если буфер не был создан ранее
		{                                  // То копируем _buff в buff
			buff = buf2d_copy(this->_buff);
		}

		buf2d_resize(buff, size.x, size.y, BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize);
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

	buf2d_set_pixel(this->_buff, x, y, color.val);
	return true;
}

bool KolibriLib::UI::Images::img::SetPixel(const Colors::Color &color, const Coord &coord)
{
	if(coord.x >= _buff->width || coord.y >= _buff->height)
		return false;
	
	buf2d_set_pixel(_buff, coord.x, coord.y, color.val);
	return true;
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(unsigned x, unsigned y) const
{
	if(x >= _buff->width || y >= _buff->height)
		throw;

	return buf2d_get_pixel(this->_buff, x, y);
}

Colors::Color KolibriLib::UI::Images::img::GetPixel(const Coord &coord) const
{
	if(coord.x >= _buff->width || coord.y >= _buff->height)
		throw;

	return buf2d_get_pixel(this->_buff, coord.x, coord.y);
}

rgb_t *KolibriLib::UI::Images::img::GetRGBMap() const
{
	if(this->_buff->color_bit == 24)
	{
		return (rgb_t*)this->_buff->buf_pointer;
	}
	return nullptr;
}

buf2d_struct *KolibriLib::UI::Images::img::GetBuff() const
{
	return this->_buff;
}

void KolibriLib::UI::Images::img::FillColor(const Colors::Color &color)
{
	buf2d_clear(this->_buff, color.val);
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
	return (Colors::Color *)this->_buff->buf_pointer;
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
			_ksys_debug_puts("Convert error\n");
		}
	}

	img_to_rgb2(buff, this->_buff->buf_pointer);
}

void KolibriLib::UI::Images::img::SetRGBMap(const rgb_t *rgbmap, const Size &size)
{
	if (this->_buff->width != size.x && this->_buff->height != size.y) // Если рамеры буфера не соответсвуют размерам rgbmap
	{													   // Изменяится размеры
		buf2d_resize(_buff, size.x, size.y, BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize);
	}

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			buf2d_set_pixel(this->_buff, j, i, Colors::RGBtoINT(rgbmap[(i * size.x) + j]));
		}
	}
}

void KolibriLib::UI::Images::img::SetColorMap(const Colors::Color *rgbmap, const Size & size)
{
	if (size != -1 && this->_buff->width != size.x && this->_buff->height != size.y) // Если рамеры буфера не соответсвуют размерам rgbmap
	{														// Изменяится размеры
		buf2d_resize(this->_buff, size.x, size.y, BUF2D_RESIZE_PARAMS::BUF2D_Resize_ChangeSize);
	}

	unsigned int* buff =(unsigned int*) malloc(size.x * size.y * sizeof(Colors::Color));
	memcpy(buff, rgbmap, size.x * size.y);
	free(_buff->buf_pointer);
	_buff->buf_pointer = buff;
}

bool KolibriLib::UI::Images::img::operator==(const img &im) const
{
	return _buff->color_bit == im._buff->color_bit &&
	       im._buff->width == _buff->width &&
           _buff->top == im._buff->top &&
		   _buff->left == im._buff->left &&
	       _buff->height == im._buff->height;
}

void KolibriLib::UI::Images::img::SetBPP(imgBPP bpp, void *data)
{
	if(bpp == _buff->color_bit)
	{
		return;
	}
	else if(bpp == img::imgBPP::RGB)
	{
		if(_buff->color_bit == img::imgBPP::RGBA)
		{
			
		}
		else if(_buff->color_bit == imgBPP::bpp8)
		{
			buf2d_conv_24_to_8(_buff, *(unsigned int*)data);
		}
	}
	else if (bpp == img::imgBPP::RGBA)
	{
		if(_buff->color_bit == imgBPP::RGB)
		{
			buf2d_conv_24_to_32(_buff, *(unsigned int*)data);
		}
		else if(true)
		{

		}
	}
	else
	{

	}
}

void KolibriLib::UI::Images::img::Rotate(int value)
{
	buf2d_rotate(_buff, value);
}

void KolibriLib::UI::Images::img::Clear(const Colors::Color &backgroundColor)
{
	buf2d_clear(_buff, backgroundColor.val);
}

void KolibriLib::UI::Images::img::DrawCircle(const Coord & coord, unsigned radius, const Colors::Color & color)
{
	buf2d_circle(_buff, coord.x, coord.y, radius, color.val);
}