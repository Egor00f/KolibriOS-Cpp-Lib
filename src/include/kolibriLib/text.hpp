#ifndef __TEXT_H__
#define __TEXT_H__


#include <sys/ksys.h>

#include <string>

#include "UI.hpp"
#include "color.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с тектсом
        namespace text
        {
            /// \brief Получить размер текста
            /// \return текущая высота текста
            inline unsigned int GetTextSize()
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
            inline void SetTextSize(unsigned int newSize)
            {
                asm_inline(
                    "int $0x40"
                    :
                    :"a"(48), "b"(12), "c"(newSize)
                );
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, Color::Color color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const char *text, const Coord &coord, const unsigned &size = 9, Color::Color color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text, coord.x, coord.y, strlen(text), color.val);
            }

            //=============================================================================================================================================================

            /// @brief Текстовая метка
            /// @paragraph Простая текстовая метка, ничего особенного.
            /// @paragraph Возможно важные сведения: текст всегда отрисовывается в середине 
            class TextLabel : public UI::UIElement
            {
            private:
                /// @brief Сам текст
                std::string _text;

                /*  Когданибудь, когда автор сего творения узнает как делать разные шрифты, эта переменная будет использоваться
                /// @brief Используемый шрифт
                std::string FontFamily;
                */

                /// @brief Размер текста(высота)
                unsigned _FontSize;

                /// @brief (Да/Нет)Подстраивать @link _FontSize, чтобы размер текст соответствовал размеру элемента( @link _size)
                bool _TextScale;

            public:
                /// @brief Конструктор
                /// @param coord координата
                /// @param size Рамер элемента, игнорируется если TextScale = false
                /// @param text Текст текста
                /// @param FontSize Размер текста
                /// @param TextScale Маштабировать текст, чтобы он не выходил за границы элемента
                /// @param Margin Отступы от границ
                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const unsigned& FontSize = 9, bool TextScale = true, const Color::Color& TextColor = OS::sys_color_table.work_text, const unsigned& Margin = 0);

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
                Color::Color GetTextColor();

                /// @brief Изменить текст
                /// @param NewText Текст
                void SetText(const std::string &NewText);

                /// @brief Изменить рамер текста
                /// @param NewTextSize Новый размер текста (в px)
                void SetFontSize(const unsigned &NewTextSize);


                /// @brief Изменить значение переменной @link _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);

                void init(Coord coord, Size size, std::string text = "TextLabel", unsigned FontSize = 9, Color::Color TextColor);

                TextLabel& operator = (const TextLabel& a)
                {
                    _coord      = a._coord;
                    _size       = a._size;
                    _MainColor  = a._MainColor;
                    _Margin     = a._Margin;
                    _text       = a._text;
                    _FontSize   = a._FontSize;
                    _TextScale  = a._TextScale;
                    return *this;
                }

            };

            TextLabel::TextLabel(const Coord& coord, const Size& size, const std::string& text, const unsigned& FontSize, bool TextScale, const Color::Color& TextColor, const unsigned& Margin) : UIElement(coord, size, TextColor, Margin)
            {
                #if DEBUG == true
                _ksys_debug_puts("TextLabel Constructor \n");
                #endif
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
                DrawText(_text, {_coord.x + (int)a, _coord.y + ((int)_size.y / 2)}, _FontSize, _MainColor);
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

            void TextLabel::SetScale(bool scale)
            {
                _TextScale = scale;
            }

            void TextLabel::init(Coord coord, Size size, std::string text, unsigned FontSize, Color::Color TextColor)
            {
                SetCoord(coord);
                SetSize(size);
                SetText(text);
                SetColor(TextColor);
                SetFontSize(FontSize);
            }
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__