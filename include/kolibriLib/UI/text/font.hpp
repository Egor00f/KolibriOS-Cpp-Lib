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
                    /// @brief инициализировать библиотеку freetype и загрузить ttf файл.
                    Font(const filesystem::Path &ttf_file);

                    Font(const Font* copy);

                    /// @brief Деструктор
                    ~Font();

                    /// @brief Загрузить шрифт из файла
                    /// @param path путь до файла
                    /// @return true если произошла ошибка
                    /// @note Изменяет значение переменной font_file
                    FT_Error loadFontFromFile(const filesystem::Path &path);

                    /// @brief Изменить размеры символов шрифта
                    /// @param size 
                    /// @note Если size.x == 0, то ширина символов выбирается автоматически
                    /// @note Изменяет значения переменных _size и _dpi
                    void SetSize(const Size &size, const Size &dpi = {0,0});

                    
                    /// @brief 
                    /// @note Вручную лучше не трогать
                    FT_Face _face;

                    /// @brief Путь до файла со шрифтом
                    filesystem::Path font_file;

                    /// @brief Размеры шрифта
                    Size _size;
                    
                    Size _dpi;

                    Font& operator =(const Font &f);
                    bool operator ==(const Font &f) const;
                    bool operator !=(const Font &f) const;
                };
            }

            

        }
    }
}

#endif // __FONTS_H__