#include <kolibri_rasterworks.h>

void *drawTextToBuff(const void *canvas, uint8_t width, uint8_t height, int x, int y, const char *string, int stringLenght, uint8_t CharWidth, uint8_t CharHeight, ksys_color_t fontColor, uint8_t flags, uint8_t encoding)
{
	const int l = height * width * 3 * sizeof(char);

	void *buff = malloc(l + 8);

	*((int *)buff) = width;
	*((int *)buff + 1) = height;

	memcpy((char *)buff + 8, canvas, l);

	if(stringLenght < 1)
	{
		stringLenght = countUTF8Z(string, -1);
	}

	drawText(buff,
			 x,
			 y,
			 string,
			 stringLenght,
			 fontColor,
			 (flags << 24) + (CharWidth << 16) + (CharHeight << 8) + encoding);

	return buff;
}