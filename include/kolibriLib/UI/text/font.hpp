#ifndef __FONTS_H__
#define __FONTS_H__

#include <kolibriLib/types.hpp>
#include <string>
#include <kolibriLib/system/os.hpp>
#include <string>
#include <kolibriLib/globals.hpp>

#include <kolibriLib/UI/text/freetypefuncs.hpp>

namespace KolibriLib
{
    namespace UI
    {
        namespace text
        {
            
            namespace Fonts
            {

                /// @brief Шрифт
                struct Font
                {
                    Font(){}
                    /// @brief инициализировать библиотеку freetype и загрузить ttf файл.
                    Font(const char *ttf_file);

                    Font(const Font* copy);

                    /// @brief Деструктор
                    ~Font();

                    /// @brief Загрузить шрифт из файла
                    /// @param path путь до файла
                    /// @return true если произошла ошибка
                    FT_Error loadFontFromTTF(const char* path);

                    /// @brief Изменить размеры символов шрифта
                    /// @param size 
                    /// @note Если size.x == 0, то ширина символов выбирается автоматически
                    void SetSize(const Size &size, const Size &dpi);

                    
                    FT_Face _face;

                    /// @brief Размеры шрифта
                    Size _size;
                };
            }

            

        }
    }
}

#endif // __FONTS_H__