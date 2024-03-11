/*
    Файл с константами
*/
#ifndef __SMALL_H__
#define __SMALL_H__

#include <string>
#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/fonts.hpp>

#define DEBUG true

namespace KolibriLib
{
    const std::string ConfigurationDir = "/kolibrios/etc/";

    const std::string ImgDir = ConfigurationDir + "KolibriOS-Cpp-Lib/";

    const std::string DefaultImage = ImgDir + "default.png";

    namespace UI
    {
        namespace text
        {
            namespace Fonts
            {
                /// @brief Высота шрифта по умолчанию
                const unsigned DefaultFontSize = 16;

                // Некоторые заготовки шрифтов

                const UI::Size Arial = {5, 6};
                const UI::Size TimesNewRoman = {4, 5};
                const UI::Size Micrhoma = {21, 11};
                const UI::Size Roboto = {7, 10};
                const UI::Size Geologica = {5, 7};

                /// @brief Шрифт по умолчанию
                const Font DefaultFont(Arial, DefaultFontSize);
            }
        }
    }

} // namespace KolibriLib

#endif // __SMALL_H__