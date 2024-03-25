#ifndef KOLIBRI_RASTERWORKS_H
#define KOLIBRI_RASTERWORKS_H

extern "C"
{

/// @brief Список параметров
enum Params
{
	/// @brief Жирный текст
	Bold = 0b1,

	/// @brief Курсив
	Italic = 0b10,

	/// @brief Нижнее подчёркивание
	Underline = 0b100,

	/// @brief Зачёркнутый
	StrikeThrough = 0b1000,

	/// @brief Выравнивание по правому краю
	AlignRight = 0b00010000,

	/// @brief Выравнивание по центру
	AlignCenter = 0b00100000,

};


/// @brief Инициализировать библиотеку RasterWorks
/// @return -1 если неудачно
extern int kolibri_rasterworks_init(void);

/// @brief Вывести текст
/// @param canvas Указатель на буффер
/// @param x координата текста по оси X
/// @param y координата текста по оси Y
/// @param string указатель на строку
/// @param charQuantity длина строки
/// @param fontColor Цвет текста
/// @param params параметры из списк @link Params
extern void (*drawText)(void *canvas, int x, int y, const char *string, int charQuantity, int fontColor, int params) __attribute__((__stdcall__));
extern int (*countUTF8Z)(const char *string, int byteQuantity) __attribute__((__stdcall__));
extern int (*charsFit)(int areaWidth, int charHeight) __attribute__((__stdcall__));
extern int (*strWidth)(int charQuantity, int charHeight) __attribute__((__stdcall__));

}
 
#endif /* KOLIBRI_RASTERWORKS_H */
