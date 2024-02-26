#include <kolibriLib/UI/image.hpp>
#include "image.hpp"

using namespace KolibriLib;
using namespace UI;

Images::Image::Image(const Coord &coord, const Size &size) : UIElement(coord, size)
{
    #ifdef DEBUG == true
    _ksys_debug_puts("I Constructor\n");
    #endif
}

Images::img::~img()
{
    img_destroy(_img);
}

void Images::img::LoadImage(const filesystem::Path &Path)
{
    int32_t img_size;
    FILE *f = fopen(Path.GetChars(), "rb"); // Этот код взят из примера из /contrib/C_Layer/EXAMPLE/img_example/main.c

    if (!f)
    {
        char *a = "LoadImage: Can't open file:";
        strcat(a, Path.GetChars());
        strcat(a, "\n");
        _ksys_debug_puts(a);
    }

    if (fseek(f, 0, SEEK_END))
    {
        char *a = "Can't SEEK_END file:";
        strcat(a, Path.GetChars());
        strcat(a, "\n");
        _ksys_debug_puts(a);
    }

    int filesize = ftell(f);
    rewind(f);
    char *fdata = (char *)malloc(filesize);

    if (!fdata)
    {
        char *a = "No memory for file:";
        strcat(a, Path.GetChars());
        strcat(a, "\n");
        strcat(a, "malloc not return ptr");
        _ksys_debug_puts(a);
    }

    img_size = (int32_t)fread(fdata, 1, filesize, f);

    if (ferror(f))
    {
        char *a = "Error reading file ";
        strcat(a, Path.GetChars());
        strcat(a, "\n");
        _ksys_debug_puts(a);
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

void Images::img::Render(const Coord& coord, const Size& size) const
{
    img_draw(_img, coord.x, coord.y, size.x, size.y, 0, 0);
}

void Images::Image::init(const Coord &coord, const Size &size, const filesystem::Path &Path)
{
    _coord = coord;
    _size = size;
    LoadImage(Path);
}

void Images::img::SetImg(Image_t *img)
{
    img_destroy(_img);
    _img = img;
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