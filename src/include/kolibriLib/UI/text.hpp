#ifndef __TEXT_H__
#define __TEXT_H__


#include <sys/ksys.h>

#include <string>
#include <assert.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibri_rasterworks.h>

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
            inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
            }


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

                /* 
                /// @brief Выравнивание по правому краю
                AlignRight = 0b00010000,

                /// @brief Выравнивание по центру
                AlignCenter = 0b00100000,
                */
            };

            /// @brief Вывести текст
            /// @param text Текст
            /// @param coord Координаты текста
            /// @param size Размеры символа(в px)
            /// @param flags Флаги
            /// @param margin Отступы границ фона от текста
            /// @param colorText Цвет текста
            /// @param BackgroundColor Цвет фона текста
            /// @warning Функция не закончена
            /// @paragraph Функция выводит текст, и фон текста
            void DrawText(const std::string &text, 
                const Coord &coord, const Size &size, 
                unsigned flags, 
                unsigned margin = 4,
                const Colors::Color &colorText = OS::sys_color_table.work_text, 
                const Colors::Color BackgroundColor = OS::sys_color_table.work_area);

            

            /// @brief Символ
            /// @paragraph Символ который может содержать как текст, так и картинку(например смайлик)
            class Char
            {
            public:
                enum Type
                {
                    None = 0,
                    Image, 
                    Text
                };

                Char(char c = ' ', const UI::Size &size, const unsigned flags = 0, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);
                Char(const Images::img& img);
                /// @brief 
                ~Char();

                /// @brief Получить тип
                /// @return значение из списка @link Type
                short GetType() const;

                void Set(const char c, const UI::Size &size, const unsigned flags = 0, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);
                void Set(const Images::Image& img);

                void SetFlags(unsigned flags);
                void SetTextColor(const Colors::Color &NewColor);
                void SetBackgroundColor(const Colors::Color &NewColor);

                char GetChar() const;

                /// @brief Отрисовать
                /// @param coord Координаты
                void Print(const UI::Coord &coord) const;

                Char& operator = (char c);
                Char& operator = (const Images::img &img);

                bool operator == (char c) const;
                bool operator == (const Images::img &img) const;
                bool operator == (const Char &img) const;
                bool operator != (char c) const;
                bool operator != (const Images::img &img) const;


            protected:
                Images::img *_img;
                char *_c;

            private:
                /// @brief Освободить все переменные
                void Free();


                UI::Size *_size;
                Colors::Color *_TextColor;
                Colors::Color *_BackgroundColor;
                unsigned *_flags;
                unsigned _type;
            };
            

            class Text
            {
            private:                
                std::vector<Char> _data;
            public:
                Text();
                ~Text();

                /// @brief Добавить символ
                /// @param c символ
                /// @param i номер 
                /// @param a заполнение
                void AddChar(const Char& c, int i = -1, const Char& a = ' ');

                /// @brief 
                /// @param coord 
                /// @param FontSize 
                void Print(const UI::Coord &coord, unsigned FontSize = 9) const;
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