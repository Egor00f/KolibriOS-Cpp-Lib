#ifndef KOLIBRI_RASTERWORKS_H
#define KOLIBRI_RASTERWORKS_H

#include <sys/ksys.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

  enum RasterworksEncoding
  {
    Rasterworks_cp688 = 1,
    Rasterworks_UTF8 = 2,
    Rasterworks_UTF16LE = 3,
  };

  /// @brief List of parameters
  enum RasterworksParams
  {
    /// @brief Bold text
    Bold = 0b1,

    /// @brief Italics
    Italic = 0b10,

    /// @brief Underscore
    Underline = 0b100,

    /// @brief Strikethrough
    StrikeThrough = 0b1000,

    /// @brief Right alignment
    AlignRight = 0b00010000,

    /// @brief Center alignment
    AlignCenter = 0b00100000,

    /// @brief 32bpp canvas insted of 24bpp
    Use32bit = 0b010000000
  };

  /// @brief Initialize the RasterWorks library
  /// @return -1 if unsuccessful
  extern int kolibri_rasterworks_init(void);

  /// @brief Draw text on 24bpp or 32bpp image
  /// @param canvas Pointer to image (array of colors)
  /// @param x Coordinate of the text along the X axis
  /// @param y Coordinate of the text along the Y axis
  /// @param string Pointer to string
  /// @param charQuantity String length
  /// @param fontColor Text color
  /// @param params ffeewwhh 
  /// hh - char height 
  /// ww - char width	; 0 = auto (proportional)
  /// ee - encoding	; 1 = cp866, 2 = UTF-16LE, 3 = UTF-8
  /// ff - Parameters from the RasterworksParams list
  /// @note All flags combinable, except align right + align center
  /// @note The text is drawn on the image, in order for changes to occur in the window, you need to draw the image after calling this function
  extern void (*drawText)(void *canvas, int x, int y, const char *string, int charQuantity, uint32_t fontColor, uint32_t params) __attribute__((__stdcall__));

  /// @brief Calculate amount of valid chars in UTF-8 string
  /// @note Supports zero terminated string (set byteQuantity = -1)
  /// @param string
  /// @param byteQuantity
  extern int (*countUTF8Z)(const char *string, int byteQuantity) __attribute__((__stdcall__));

  /// @brief Calculate amount of chars that fits given width
  extern int (*charsFit)(int areaWidth, int charHeight) __attribute__((__stdcall__));

  /// @brief Calculate string width in pixels
  /// @param charQuantity Characters
  /// @param charHeight character height
  extern int (*strWidth)(int charQuantity, int charHeight) __attribute__((__stdcall__));

  /// @brief 
  /// @param canvas 
  /// @param width 
  /// @param height 
  /// @param x 
  /// @param y 
  /// @param string 
  /// @param stringLenght 
  /// @param CharWidth 
  /// @param CharHeight 
  /// @param fontColor 
  /// @param flags 
  /// @param encoding 
  /// @return 
  void *drawTextToBuff(const void *canvas,
                       uint8_t width, 
                       uint8_t height, 
                       int x, 
                       int y, 
                       const char *string, 
                       int stringLenght, 
                       uint8_t CharWidth,
                       uint8_t CharHeight, 
                       ksys_color_t fontColor, 
                       uint8_t flags, 
                       uint8_t encoding);

#ifdef __cplusplus
}

#include <kolibriLib/types.hpp>
#include <string>

/// @brief 
/// @param canvas буффер
/// @param coord координаты текста в буфере
/// @param size размеры буфера
/// @param text текст
/// @param CharSize Размеры символов
/// @param FontColor цвет текста
/// @param flags флаги
/// @param encoding 
/// @return
inline void *drawTextToBuff(const void *canvas, const KolibriLib::Coord &coord, const KolibriLib::Size &size, const std::string &text, const KolibriLib::Size &CharSize, const KolibriLib::Colors::Color &FontColor, const uint8_t &flags, const uint8_t encoding = RasterworksEncoding::Rasterworks_UTF8)
{
  return drawTextToBuff(canvas, size.x, size.y, coord.x, coord.y, text.c_str(), text.length(), CharSize.x, CharSize.y, FontColor, flags, encoding);
}

inline void drawtext(const KolibriLib::Coord &coord, const KolibriLib::Size &size, const std::string &text, const KolibriLib::Size &CharSize, const KolibriLib::Colors::Color &FontColor, const KolibriLib::Colors::Color &BackgroundColor, const uint8_t &flags, const uint8_t encoding = RasterworksEncoding::Rasterworks_UTF8)
{
  void *canvas = malloc(3 * size.x * size.y);

  for(std::size_t i = 0; i < size.x * size.y; i++)
  {
    ((rgb_t *)canvas)[i] = BackgroundColor.GetRGB();
  }

  void *buff = drawTextToBuff(canvas, {0,0}, size, text, CharSize, FontColor, flags, encoding);
  free(canvas);
  _ksys_draw_bitmap(buff, coord.x, coord.y, size.x, size.y);
  free(buff);
	
}


#endif

#endif /* KOLIBRI_RASTERWORKS_H */
