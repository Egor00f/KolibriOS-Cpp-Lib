/* Written by turbocat2001 (Logaev Maxim) */

#ifndef KOLIBRI_LIBIMG_H
#define KOLIBRI_LIBIMG_H


extern "C"
{

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int kolibri_libimg_init(void);

#define _stdcall __attribute__((__stdcall__))


#pragma pack(push, 1)
	/// @brief Image
	typedef struct
	{
		/// @brief ((Width ROL 16) OR Height) XOR Data[0]
		/// @note Ignored so far
		uint32_t Checksum;

		/// @brief Image width
		uint32_t Width;

		/// @brief Image height
		uint32_t Height;

		uint32_t Next;

		uint32_t Previous;

		/// @brief One of Image bppN
		uint32_t Type;

		/// @brief Image, array of colors
		uint32_t *Data;

		/// @brief Used if Type eq Image.bpp1, Image.bpp2, Image.bpp4 or Image.bpp8i
		uint32_t Palette;

		uint32_t Extended;

		/// @brief Bitfield
		uint32_t Flags;

		/// @brief Used if Image is animated is set in Flags
		uint32_t Delay;

	} Image_t;
#pragma pack(pop)

/// @brief List of bppN
enum BPP
{
	/// @brief indexed
	IMAGE_BPP8i = 1,
	/// @brief "True color" 24bit
	IMAGE_BPP24 = 2,
	/// @brief 32bit
	IMAGE_BPP32 = 3,
	IMAGE_BPP15 = 4,
	/// @brief 16bit
	IMAGE_BPP16 = 5,
	IMAGE_BPP1 = 6,
	/// @brief grayscale
	IMAGE_BPP8g = 7,
	IMAGE_BPP2i = 8,
	IMAGE_BPP4i = 9,
	IMAGE_BPP8a = 10
};

/// @brief List of format id's
enum Formats
{
	/// @brief bmp format
	LIBIMG_FORMAT_BMP = 1,
	/// @brief ico format
	LIBIMG_FORMAT_ICO = 2,
	/// @brief cur format
	LIBIMG_FORMAT_CUR = 3,
	/// @brief gif format
	LIBIMG_FORMAT_GIF = 4,
	/// @brief png format
	LIBIMG_FORMAT_PNG = 5,
	/// @brief jpeg format
	LIBIMG_FORMAT_JPEG = 6,
	/// @brief tga format
	LIBIMG_FORMAT_TGA = 7,
	/// @brief pcx format
	LIBIMG_FORMAT_PCX = 8,
	/// @brief xcf format
	LIBIMG_FORMAT_XCF = 9,
	/// @brief tiff format
	LIBIMG_FORMAT_TIFF = 10,
	/// @brief Portable anymap format
	LIBIMG_FORMAT_PNM = 11,
	/// @brief Wireless Application Protocol Bitmap format
	LIBIMG_FORMAT_WBMP = 12,
	/// @brief X BitMap format
	LIBIMG_FORMAT_XBM = 13,

	LIBIMG_FORMAT_Z80 = 14
};

/// @brief List of scale type
enum Scale
{
	LIBIMG_SCALE_NONE = 0,
	LIBIMG_SCALE_INTEGER = 1,
	LIBIMG_SCALE_TILE = 2,
	LIBIMG_SCALE_STRETCH = 3,
	LIBIMG_SCALE_FIT_BOTH = LIBIMG_SCALE_STRETCH,
	LIBIMG_SCALE_FIT_MIN = 4,
	LIBIMG_SCALE_FIT_RECT = LIBIMG_SCALE_FIT_MIN,
	LIBIMG_SCALE_FIT_WIDTH = 5,
	LIBIMG_SCALE_FIT_HEIGHT = 6,
	LIBIMG_SCALE_FIT_MAX = 7
};   

/// @brief List of interpolation algorithms
enum Inter
{
	/// @note use it with LIBIMG_SCALE_INTEGER, LIBIMG_SCALE_TILE, etc
	LIBIMG_INTER_NONE = 0,
	/// @brief Bilinear algorithm
	LIBIMG_INTER_BILINEAR = 1,
	/// @brief Bicubic algorithm
	LIBIMG_INTER_BICUBIC = 2,
	/// @brief Lanczos algorithm
	LIBIMG_INTER_LANCZOS = 3,
	/// @brief Default algorithm
	LIBIMG_INTER_DEFAULT = LIBIMG_INTER_BILINEAR
};

/// @brief error codes
enum Errors
{
	LIBIMG_ERROR_OUT_OF_MEMORY = 1,
	LIBIMG_ERROR_FORMAT = 2,
	LIBIMG_ERROR_CONDITIONS = 3,
	LIBIMG_ERROR_BIT_DEPTH = 4,
	LIBIMG_ERROR_ENCODER = 5,
	LIBIMG_ERROR_SRC_TYPE = 6,
	LIBIMG_ERROR_SCALE = 7,
	LIBIMG_ERROR_INTER = 8,
	LIBIMG_ERROR_NOT_INPLEMENTED = 9,
	LIBIMG_ERROR_INVALID_INPUT = 10
};

/// @brief encode flags (byte 0x02 of _common option)
enum Encode
{
	LIBIMG_ENCODE_STRICT_SPECIFIC = 0x01,
	LIBIMG_ENCODE_STRICT_BIT_DEPTH = 0x02,
	LIBIMG_ENCODE_DELETE_ALPHA = 0x08,
	LIBIMG_ENCODE_FLUSH_ALPHA = 0x10
};

enum Flip
{
	FLIP_VERTICAL = 0x01,
	FLIP_HORIZONTAL = 0x02
};

enum Rotate
{
	ROTATE_90_CW = 0x01,
	ROTATE_180 = 0x03,
	ROTATE_270_CW = 0x03,
	ROTATE_90_CCW = ROTATE_270_CW,
	ROTATE_270_CCW = ROTATE_90_CW

};

extern Image_t*   (*img_decode)(void* file_data, uint32_t size, uint32_t b_color) _stdcall;
extern Image_t*   (*img_encode)(Image_t* img, uint32_t length, uint32_t option) _stdcall;
extern Image_t*   (*img_create)(uint32_t width, uint32_t height, uint32_t type) _stdcall;
extern void     (*img_to_rgb2)(Image_t* img, void *rgb_data) _stdcall;
extern Image_t*   (*img_to_rgb)(Image_t* img) _stdcall;
extern bool     (*img_flip)(Image_t* img, uint32_t flip) _stdcall;
extern bool     (*img_flip_layer)(Image_t *img, uint32_t flip) _stdcall;
extern bool     (*img_rotate)(Image_t *img, uint32_t rotate) _stdcall;
extern bool     (*img_rotate_layer)(Image_t* data, uint32_t rotate) _stdcall;
extern void     (*img_draw)(Image_t *img, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t xoff,  uint32_t yoff) _stdcall;
extern int32_t  (*img_count)(Image_t *img) _stdcall;
extern bool     (*img_destroy)(Image_t *img) _stdcall;
extern bool     (*img_destroy_layer)(Image_t* img) _stdcall;
extern Image_t*   (*img_blend)(Image_t* dst, Image_t* src, uint32_t out_x, uint32_t out_y, uint32_t in_x, uint32_t in_y, uint32_t width, uint32_t height) _stdcall; 
extern Image_t*   (*img_convert)(Image_t *src, Image_t *dst, uint32_t dst_type, uint32_t, uint32_t) _stdcall; 
extern Image_t*   (*img_resize_data)(Image_t *src, uint32_t width, uint32_t height) _stdcall;
extern Image_t*   (*img_scale)(Image_t* src, uint32_t crop_x, uint32_t crop_y, uint32_t crop_width, uint32_t crop_height, Image_t* dst, uint32_t scale_type, uint32_t inter, uint32_t new_width, uint32_t new_height) _stdcall;

} // extern "C"

#ifdef __MakeStaticLib__
/// @brief Загрузить изображение из файла
/// @param Path путь до файла
/// @return Указатель на картинку
inline Image_t* LoadImageFromFile(const char* Path)
{
	int32_t img_size;
	FILE *f = fopen(Path, "rb"); // Этот код взят из примера из /contrib/C_Layer/EXAMPLE/img_example/main.c

	if (!f)
	{
		const char a[] = "LoadImage: Can't open file: ";
		char *b;
		strcat(b, a);
		strcat(b, Path);
		strcat(b, " \n \0");
		_ksys_debug_puts(b);
	}

	if (fseek(f, 0, SEEK_END))
	{
		const char a[] = "Can't SEEK_END file: ";
		char *b;
		strcat(b, a);
		strcat(b, Path);
		strcat(b, " \n \0");
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
		strcat(b, Path);
		strcat(b, "\n");
		strcat(b, "malloc not return ptr\n\0");
		_ksys_debug_puts(b);
	}

	img_size = (int32_t)fread(fdata, 1, filesize, f);

	if (ferror(f))
	{
		const char *a = "Error reading file ";
		char *b;
		strcat(b, a);
		strcat(b, Path);
		strcat(b, " \n \0");
		_ksys_debug_puts(b);
	}

	fclose(f);

	Image_t *buff = img_decode((void *)fdata, img_size, 0);

	free(fdata);

	return buff;
}
#endif

inline void img_fill_color(Image_t* img, uint32_t width, uint32_t height, uint32_t color) {
    uint32_t i;
    for (i = 0; i < width*height; i++) {
        img->Data[i] = color;
    }
}

/// @brief Fill the image with color
/// @param img image
/// @param color Сolor
inline void img_fill_color(Image_t *img, uint32_t color)
{
	for (uint32_t i = 0; i < img->Width * img->Height; i++)
	{
		img->Data[i] = color;
	}
}



#endif /* KOLIBRI_LIBIMG_H */
