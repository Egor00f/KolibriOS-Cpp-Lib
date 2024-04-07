#include <kolibri_buf2d.h>

buf2d_struct *buf2d_create(uint16_t tlx, uint16_t tly, unsigned int sizex, unsigned int sizey, unsigned int font_bgcolor, uint8_t color_bit)
{
    buf2d_struct *new_buf2d_struct = (buf2d_struct *) malloc(sizeof(buf2d_struct));
    new_buf2d_struct -> left = tlx;
	new_buf2d_struct -> top = tly;
	new_buf2d_struct -> width = sizex;
	new_buf2d_struct -> height = sizey;
	new_buf2d_struct -> bgcolor = font_bgcolor;
	new_buf2d_struct -> color_bit = color_bit;
	buf2d_create_asm(new_buf2d_struct);
    return new_buf2d_struct;
}

buf2d_struct *buf2d_copy(const buf2d_struct *buff)
{
	buf2d_struct *b = (buf2d_struct *)malloc(sizeof(buf2d_struct));
	memcpy(b, buff, sizeof(buf2d_struct));
	return b;
}



