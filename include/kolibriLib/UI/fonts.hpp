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
            /// @paragraph На самом деле это не настоящие шрифты, а лишь жалкие пародии, совподающие с настоящими лишь по размерам(ширина/высота)
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

                /// @brief Шрифт
                struct Font
                {
                    /// @brief
                    /// @param FontFamily Шрифт, фактически это соотношение сторон
                    /// @param FontSize Высота шрифта
                    Font(const UI::Size &FontFamily = Arial, int FontSize = DefaultFontSize, unsigned flags = Flags::Normal);

                    /// @brief Изменить размер шрифта
                    /// @param FontSize
                    void SetFontSize(unsigned FontSize);

                    UI::Size _Font;
                    unsigned _FontSize;
                    unsigned _Flags;

                    mutable UI::Size size;

                    Font &operator=(const Font &f);

                    bool operator==(const Font &f) const;
                };

                /// @brief Шрифт по умолчанию
                const Font DefaultFont(Arial, DefaultFontSize);
            };
        }
    }
}

#endif // __FONTS_H__