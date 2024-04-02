/*
	Список шрифотв
*/
#ifndef __FONTS_LIST_HPP__
#define __FONTS_LIST_HPP__

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/text/fonts.hpp>

namespace KolibriLib
{
    namespace UI
    {
        namespace text
        {
            namespace Fonts
            {
                /// @brief Высота шрифта по умолчанию
                const unsigned DefaultFontSize = 16;

                // Некоторые заготовки шрифтов
				// ээти шрифты лишь похожи на оригинальные
				
                const Size System = {1, 0};
                const Size Arial = {5, 6};
                const Size TimesNewRoman = {4, 5};
                const Size Micrhoma = {21, 11};
                const Size Roboto = {7, 10};
                const Size Geologica = {5, 7};

                /// @brief Шрифт по умолчанию
                const Font DefaultFont(Arial, DefaultFontSize);
            }
        }
    }
}

#endif