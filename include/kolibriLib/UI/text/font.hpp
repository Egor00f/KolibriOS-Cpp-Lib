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

                    /// @brief Загрузить шрифт из файла
                    /// @param path путь до файла
                    /// @return true если произошла ошибка
                    bool loadFontFromTTF(const char* path);

                    /// @brief Изменить размеры символов шрифта
                    /// @param size 
                    /// @note Если size.x == 0, то ширина символов выбирается автоматически
                    void SetSize(const Size &size);

                    
                    FT_Face _face;
                    Size _size;
                };
            }

            

            /// @brief 
            /// @param text 
            /// @param font 
            /// @param coord 
            void DrawText(const std::string &text, const Fonts::Font &font, Coord coord);
        }
    }
}

#endif // __FONTS_H__