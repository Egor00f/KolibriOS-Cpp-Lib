#ifndef __TEXT_H__
#define __TEXT_H__


#include <sys/ksys.h>

#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/UI/image.hpp>

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
            inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, Colors::Color color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
            }

            /// \brief Вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            inline void DrawText(const char *text, const Coord &coord, const unsigned &size = 9, Colors::Color color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text, coord.x, coord.y, strlen(text), color.val);
            }

            class Text
            {
            private:
                struct image
                {
                    unsigned pos;
                    Images::Image img;
                };
                
                std::string _text;
                std::vector<image> _imgs;
            public:
                Text();
                ~Text();

                void Render(UI::Coord coord, unsigned FontSize = 9);
            };
            

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
                mutable unsigned _FontSize;

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
                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const unsigned& FontSize = 9, bool TextScale = true, const Colors::Color& TextColor = OS::sys_color_table.work_text, const unsigned& Margin = 0);

                ~TextLabel();

                /// @brief Отрисовать текстовую метку
                void Render() const;

                /// @brief Получить текст
                /// @return Функция возвращает @link _text
                const std::string &GetText() const;

                /// @brief Получить Размер шрифта
                /// @return Функция возвращает @link _FontSize
                unsigned GetFontSize() const;


                /// @brief Изменить текст
                /// @param NewText Текст
                void SetText(const std::string &NewText);

                /// @brief Изменить рамер текста
                /// @param NewTextSize Новый размер текста (в px)
                void SetFontSize(const unsigned &NewTextSize);


                /// @brief Изменить значение переменной @link _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);

                void init(Coord coord, Size size, std::string text = "TextLabel", unsigned FontSize = 9, Colors::Color TextColor = OS::sys_color_table.work_text);

                /// @brief 
                /// @param a 
                /// @return 
                TextLabel& operator = (const TextLabel& a);

                /// @brief 
                /// @param a 
                /// @return 
                bool operator == (const TextLabel& a) const;
            };

            
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__