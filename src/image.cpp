#include <kolibriLib/UI/image.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace Images;

Image::Image(const Coord &coord, const Size &size) : UIElement(coord, size), img(OS::GetSystemColors().work_graph, size)
{
	_ksys_debug_puts("KolibriLib::UI::Images::Image Constructor");
}

void img::LoadImage(const filesystem::Path &Path)
{
	int32_t img_size;
	FILE *f = fopen(Path.GetChars(), "rb"); // Этот код взят из примера из /contrib/C_Layer/EXAMPLE/img_example/main.c

	if (!f)
	{
		const char a[] = "LoadImage: Can't open file: ";
		char *b;
		strcat(b, a);
		strcat(b, Path.GetChars());
		strcat(b, " \n ");
		_ksys_debug_puts(b);
	}

	if (fseek(f, 0, SEEK_END))
	{
		const char a[] = "Can't SEEK_END file: ";
		char *b;
		strcat(b, a);
		strcat(b, Path.GetChars());
		strcat(b, " \n ");
		_ksys_debug_puts(b);
	}

	int filesize = ftell(f);
	rewind(f);
	char *fdata = (char *)malloc(filesize);

	if (!fdata)
	{
		const char a[] = "No memory for file: ";
		char *b;
		strcat(b, a);
		strcat(b, Path.GetChars());
		strcat(b, "\n");
		strcat(b, "malloc not return ptr\n");
		_ksys_debug_puts(b);
	}

	img_size = (int32_t)fread(fdata, 1, filesize, f);

	if (ferror(f))
	{
		const char *a = "Error reading file ";
		char *b;
		strcat(b, a);
		strcat(b, Path.GetChars());
		strcat(b, " \n ");
		_ksys_debug_puts(b);
	}

	fclose(f);

	_img = img_decode((void *)fdata, img_size, 0);

	free(fdata);

	if (_img->Type != IMAGE_BPP32)
	{
		_img = img_convert(_img, NULL, IMAGE_BPP32, 0, 0); // Convert image to format BPP32
		if (!_img)
		{
			_ksys_debug_puts("Convert error");
		}
	}
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