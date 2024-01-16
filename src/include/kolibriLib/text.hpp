#ifndef __TEXT_H__
#define __TEXT_H__


#include <sys/ksys.h>

#include <string>

#include "UI.hpp"


namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с тектсом
        namespace text
        {
            /// \brief Получить размер текста
            /// \return текущая высота текста
            unsigned int GetTextSize()
            {
                unsigned Size;
                asm_inline(
                    "int $0x40"
                    : "=c"(Size)
                    : "a"(48), "b"(11));
                return Size;
            }

            /// \brief Изменить размер текста
            /// \param newSize высота текста в px
            void SetTextSize(unsigned int newSize)
            {
                asm_inline(
                    "int $0x40" ::"a"(48), "b"(12), "c"(newSize));
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const std::string &text, const point<unsigned> &coord, const unsigned &size = 9, ksys_color_t color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color);
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const char *text, const point<unsigned> &coord, const unsigned &size = 9, ksys_color_t color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text, coord.x, coord.y, strlen(text), color);
            }

            //=============================================================================================================================================================

            /// @brief Текстовая метка
            class TextLabel : public UIElement
            {
            private:
                /// @brief Сам текст
                std::string _text;

                /// @brief Используемый шрифт
                std::string FontFamily;
                
                /// @brief Размер текста(высота)
                unsigned _FontSize;

                /// @brief Подстраивать @link _FontSize, чтобы размер текст соответствовал размеру элемента( @link _size)
                bool _TextScale;

                
            public:
                /// @brief Конструктор
                /// @param coord координата
                /// @param size Рамер элемента, игнорируется если TextScale = false
                /// @param text Текст текста
                /// @param FontSize Размер текста
                /// @param TextScale Маштабировать текст, чтобы он не выходил за границы элемента
                /// @param Margin Отступы от границ
                TextLabel(point<unsigned> coord = {0, 0}, point<unsigned> size = {16, 16}, std::string text = "Text", unsigned FontSize = 9, bool TextScale = true, ksys_color_t TextColor = OS::sys_color_table.work_text, unsigned Margin = 0);

                ~TextLabel();

                /// @brief Отрисовать текстовую метку
                void Render();

                /// @brief Получить текст
                /// @return @link _text
                std::string GetText();

                /// @brief Получить Размер шрифта
                /// @return @link _FontSize
                unsigned GetFontSize();

                /// @brief Получить цвет текста
                /// @return @link _TextColor
                ksys_color_t GetTextColor();

                /// @brief Изменить текст
                /// @param NewText Текст
                void SetText(const std::string &NewText);

                /// @brief Изменить рамер текста
                /// @param NewTextSize Новый размер текста (в px)
                void SetFontSize(const unsigned &NewTextSize);

                /// @brief Изменить цвет текста
                /// @param NewTextColor Новый цвет текста
                void SetTextColor(const ksys_color_t &NewTextColor);

                /// @brief Изменить значение переменной @link _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);
            };

            TextLabel::TextLabel(point<unsigned> coord, point<unsigned> size, std::string text, unsigned FontSize, bool TextScale, ksys_color_t TextColor, unsigned Margin) : UIElement(coord, size, TextColor, Margin)
            {
                _text = text;
                _FontSize = FontSize;
                _TextScale = TextScale;
            }

            TextLabel::~TextLabel()
            {
            }

            void TextLabel::Render()
            {
                if (_TextScale) // Если текст нужно подстраивать размер, то
                {               // Постраиваем
                    _FontSize = _size.x / _text.length();
                }

                unsigned a = _Margin;

                if ((_text.length() * _FontSize) > _size.x) // Центрирование текста
                {
                    a = (_size.x / 2) - (_text.length() * _FontSize);
                }

                SetTextSize(_FontSize);
                DrawText(_text, {_coord.x + a, _coord.y + (_size.y / 2)}, _FontSize, _MainColor);
            }

            std::string TextLabel::GetText()
            {
                return _text;
            }
            unsigned TextLabel::GetFontSize()
            {
                return _FontSize;
            }

            void TextLabel::SetText(const std::string &NewText)
            {
                _text = NewText;
            }
            void TextLabel::SetFontSize(const unsigned &NewTextSize)
            {
                _FontSize = NewTextSize;
            }


            void TextLabel::SetTextColor(const ksys_color_t &NewTextColor)
            {
                _MainColor = NewTextColor;
            }

            void TextLabel::SetScale(bool scale)
            {
                _TextScale = scale;
            }

            ksys_color_t TextLabel::GetTextColor()
            {
                return _MainColor;
            }
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__