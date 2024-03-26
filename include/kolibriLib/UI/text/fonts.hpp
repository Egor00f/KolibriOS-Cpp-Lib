#ifndef __FONTS_H__
#define __FONTS_H__

#include <kolibriLib/types.hpp>

namespace KolibriLib
{
    namespace UI
    {
        namespace text
        {
            /// @brief Флаги для RasterWorks
            enum Flags
            {
                /// @brief Обычный текст
                /// @note Указывать не обязательно
                Normal = 0b0000,

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

            /// @brief Пародия на шрифты
            /// @note На самом деле это не настоящие шрифты, а лишь жалкие пародии, совподающие с настоящими лишь по размерам(ширина/высота)
            namespace Fonts
            {
                

                /// @brief Шрифт
                struct Font
                {
                    /// @brief
                    /// @param FontFamily Шрифт, фактически это соотношение сторон
                    /// @param FontSize Высота шрифта
                    Font(const Size &FontFamily = Size(5, 6), int FontSize = 16, unsigned flags = Flags::Normal);

                    /// @brief Изменить размер шрифта
                    /// @param FontSize
                    void SetFontSize(unsigned FontSize);

                    /// @brief Шрифт
                    Size _Font;
                    /// @brief Высота шрифта
                    unsigned _FontSize;
                    /// @brief Флаги
                    unsigned _Flags;

                    /// @brief Размер текста для функции DrawText()
                    mutable Size size;

                    Font &operator=(const Font &f);

                    bool operator==(const Font &f) const;
                };
            };
        }
    }
}

#endif // __FONTS_H__