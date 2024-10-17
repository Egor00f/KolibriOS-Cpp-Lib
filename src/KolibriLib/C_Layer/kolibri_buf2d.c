#include <C_Layer/INCLUDE/kolibri_buf2d.h>

buf2d_struct *buf2d_create(uint16_t tlx, uint16_t tly, unsigned int sizex, unsigned int sizey, ksys_color_t font_bgcolor, uint8_t color_bit)
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

void buf2d_curve_bezier(buf2d_struct *buf, ksys_pos_t p1, ksys_pos_t p2, ksys_pos_t p3, ksys_color_t color)
{
	buf2d_curve_bezier_asm(
		buf, 
		(uint32_t)((p1.x << 16) + p1.y),
		(uint32_t)((p2.x << 16) + p2.y), 
		(uint32_t)((p3.x << 16) + p3.y), 
		color);
}

buf2d_struct *buf2d_copy(const buf2d_struct *buff, buf2d_struct* copy)
{
	copy = (buf2d_struct *) malloc(sizeof(buf2d_struct));
	
	memcpy(copy, buff, sizeof(buf2d_struct));
	
	return copy;
}

buf2d_struct *buf2d_conv_32_to_24(const buf2d_struct *buffer32bit, buf2d_struct *buffer24bit)
{
	if(buffer24bit == NULL)	// Если 24 битный бувер не указан
	{                      	// То нужно его создать
		buffer24bit = buf2d_create(0, 0, buffer32bit->width, buffer32bit->height, 0xFFFFFF, 24);
	}

	for (unsigned i = 0; i < (buffer32bit->width * buffer32bit->height); i++)
	{
		((rgb_t *)buffer24bit->buf_pointer)[i] = (rgb_t) {
			buffer32bit->buf_pointer[i] << 24, 
			buffer32bit->buf_pointer[i] << 16, 
			buffer32bit->buf_pointer[i] << 8
		};
	}
	return buffer24bit;
}

