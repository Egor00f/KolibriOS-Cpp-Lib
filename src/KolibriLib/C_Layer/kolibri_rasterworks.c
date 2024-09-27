#include <C_Layer/INCLUDE/kolibri_rasterworks.h>

void *drawTextToBuff(const void *canvas, uint8_t width, uint8_t height, int x, int y, const char *string, int stringLenght, uint8_t CharWidth, uint8_t CharHeight, ksys_color_t fontColor, uint8_t flags, uint8_t encoding)
{
	const size_t l = height * width * 3U * sizeof(char);

	void *buff = malloc(l + 8U);

	*((int *)buff)	= width;
	*((int *)buff + 1)	= height;

	if(canvas != NULL)
	{
		memcpy(((char *)buff) + 8, canvas, l);
	}
	else
	{
		memset(buff + 8, -1, l);
	}

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
			 (uint32_t)(flags << 24) | (encoding << 16) | (CharWidth << 8) | (CharHeight));

	return buff;
}