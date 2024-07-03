#include <C_Layer/INCLUDE/kolibri_libimg.h>

Image_t* LoadImageFromFile(const char* Path)
{
	int32_t img_size;
	FILE *f = fopen(Path, "rb"); // Этот код взят из примера из /contrib/C_Layer/EXAMPLE/img_example/main.c

	if (!f)
	{
		char *b;
		strcat(b, "LoadImage: Can't open file: ");
		strcat(b, Path);
		strcat(b, " \n \0");
		_ksys_debug_puts(b);
	}

	if (fseek(f, 0, SEEK_END))
	{
		char *b;
		strcat(b, "Can't SEEK_END file: ");
		strcat(b, Path);
		strcat(b, " \n \0");
		_ksys_debug_puts(b);
	}

	int filesize = ftell(f);
	rewind(f);
	char *fdata = (char *)malloc(filesize);

	if (!fdata)
	{
		char *b;
		strcat(b, "No memory for file: ");
		strcat(b, Path);
		strcat(b, "\nmalloc not return ptr\n\0");
		_ksys_debug_puts(b);
	}

	img_size = (int32_t)fread(fdata, 1, filesize, f);

	if (ferror(f))
	{
		char *b;
		strcat(b, "Error reading file ");
		strcat(b, Path);
		strcat(b, " \n \0");
		_ksys_debug_puts(b);
	}

	fclose(f);

	Image_t *buff = img_decode((void *)fdata, img_size, 0);

	free(fdata);

	return buff;
}

Image_t *img_Copy(const Image_t *src)
{
	Image_t *copy = img_create(src->Width, src->Height, src->Type);

	memcpy(copy, src, sizeof(Image_t));

	return copy;
}

void img_fill_color(Image_t *img, uint32_t color)
{
	for (uint32_t i = 0; i < img->Width * img->Height; i++)
	{
		img->Data[i] = color;
	}
}