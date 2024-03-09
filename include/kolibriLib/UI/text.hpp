#ifndef __TEXT_H__
#define __TEXT_H__


#include <sys/ksys.h>

#include <string>
#include <assert.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibri_rasterworks.h>
#include "fonts.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с тектсом
        namespace text
        {
            /// \brief Получить размер текста
            /// \return текущая высота текста
            /// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
            inline unsigned int GetTextSize()
            {
                unsigned Size;
                asm_inline(
                    "int $0x40"
                    : "=c"(Size)
                    : "a"(48), "b"(11)
                );
                return Size;
            }

            /// \brief Изменить размер текста
            /// \param newSize высота текста в px
            /// @warning Функция действует только для текста выводимого через функцию @link DrawText(const std::string &text, const Coord &coord, const unsigned &size, const Colors::Color &color)
            inline void SetTextSize(unsigned newSize)
            {
                asm_inline(
                    "int $0x40"
                    ::"a"(48), "b"(12), "c"(newSize)
                );
            }

            /// \brief Просто вывести текст
            /// \param text текст
            /// \param coord координаты
            /// \param color цвет текста
            /// @paragraph Для изменения высоты шрифта используйте @link SetTextSize(unsigned)
            inline void DrawText(const std::string &text, const Coord &coord, const unsigned &size = 9, const Colors::Color &color = OS::sys_color_table.work_text)
            {
                SetTextSize(size);
                _ksys_draw_text(text.c_str(), coord.x, coord.y, text.length(), color.val);
            }

            /// @brief Вывести текст
            /// @param text Текст
            /// @param coord Координаты текста
            /// @param size Размеры символа(в px)
            /// @param flags Флаги
            /// @param margin Отступы границ фона от текста
            /// @param colorText Цвет текста
            /// @param BackgroundColor Цвет фона текста
            /// @paragraph Функция выводит текст, и фон текста, используя библиотеку RasterWorks
            /// @example DrawText("Text", {0,0}, Fonts::Font(Fonts::Arial, 16).size); //16 - высота шрифта
            /// @example DrawText("Text", {0,0}, Fonts::Font(Fonts::Michroma, 12, Italic).size); //16 - высота шрифта
            void DrawText(const std::string &text,
                          const Coord &coord, const Size &size = Fonts::DefaultFont.size,
                          unsigned flags = Flags::Normal,
                          unsigned margin = UI::DefaultMargin,
                          const Colors::Color &colorText = OS::sys_color_table.work_text,
                          const Colors::Color &BackgroundColor = OS::sys_color_table.work_area)
            {
                const unsigned w = ((margin * 2) + size.x);
                const unsigned h = ((margin * 2) + (size.y * text.length()));

                rgb_t *canvas = new rgb_t[w * h];

                if(BackgroundColor._a < 1)
                {                           //прозрачность фона
                    const float k = BackgroundColor._a / 255;
                    for (int i = 0; i < h; i++)
                    {
                        for (int j = 0; j < w; i++)
                        {
                            canvas[i * h + j] = Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0)),
                                                                    BackgroundColor,
                                                                    k)
                                                    .GetRGB();
                        }
                    }
                }
                else
                {
                    memset((void*)canvas, Colors::RGBtoINT(BackgroundColor.GetRGB()), w * h);
                }


                drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, flags);

                if(colorText._a < 1)
                {                       //Прозрачность текста
                    const float k = colorText._a / 255;
                    for (int i = margin; i < h - margin; i++)   //Трогать поля нет смысла
                    {
                        for (int j = margin; j < w - margin; i++)
                        {
                            Colors::Color b = graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0));
                            if (b != canvas[i * (h - margin) + j])
                            {
                                canvas[i * (h - margin) + j] = Colors::BlendColors(b,
                                                                               canvas[i * (h - margin) + j],
                                                                               k)
                                                                .GetRGB();
                            }
                            
                        }
                    }
                }

                _ksys_draw_bitmap(canvas, coord.x, coord.y, w, h);

                delete[] canvas;
            }

            /// @brief Вывести текст
            /// @param text Текст
            /// @param coord Координаты
            /// @param font Шрифт
            /// @param margin Отступы границ фона от текста
            /// @param colorText цвет текста
            /// @param BackgroundColor цвет фона
            /// @paragraph Функция выводить используя библиотеку RasterWorks
            void DrawText(const std::string &text,
                          const Coord &coord, const Fonts::Font &font = Fonts::DefaultFont,
                          unsigned margin = UI::DefaultMargin,
                          const Colors::Color &colorText = OS::sys_color_table.work_text,
                          const Colors::Color &BackgroundColor = OS::sys_color_table.work_area)
            {
                const unsigned w = ((margin * 2) + font.size.x);
                const unsigned h = ((margin * 2) + (font.size.y * text.length()));

                rgb_t *canvas = new rgb_t[w * h];

                if (BackgroundColor._a < 1)
                { // прозрачность фона
                    const float k = BackgroundColor._a / 255;
                    for (int i = 0; i < h; i++)
                    {
                        for (int j = 0; j < w; i++)
                        {
                            canvas[i * h + j] = Colors::BlendColors(graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0)),
                                                                    BackgroundColor,
                                                                    k)
                                                    .GetRGB();
                        }
                    }
                }
                else
                {
                    memset((void *)canvas, Colors::RGBtoINT(BackgroundColor.GetRGB()), w*h);
                }

                drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, font._Flags);

                if (colorText._a < 1)
                { // Прозрачность текста
                    const float k = colorText._a / 255;
                    for (int i = margin; i < h - margin; i++) // Трогать поля нет смысла
                    {
                        for (int j = margin; j < w - margin; i++)
                        {
                            Colors::Color b = graphic::ReadPoint(window::GetWindowCoord() + coord + Coord(0, i) + Coord(j, 0));
                            if (b != canvas[i * (h - margin) + j])
                            {
                                canvas[i * (h - margin) + j] = Colors::BlendColors(b,
                                                                                   canvas[i * (h - margin) + j],
                                                                                   k)
                                                                   .GetRGB();
                            }
                        }
                    }
                }

                _ksys_draw_bitmap(canvas, coord.x, coord.y, w, h);

                delete[] canvas;
            }

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

                /// @brief Конструктор
                /// @param c символ
                /// @param size размеры символа
                /// @param flags флаги
                /// @param TextColor Цвет текста
                /// @param BackgroundColor Цвет фона
                Char(char c = ' ', const Fonts::Font& font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);

                /// @brief Конструктор
                /// @param img изображение
                Char(const Images::img& img, const Fonts::Font& font = Fonts::DefaultFont);

                /// @brief Деструктор
                ~Char();

                /// @brief Получить тип
                /// @return значение из списка @link Type
                short GetType() const;

                /// @brief 
                /// @param c 
                /// @param size Размер символа
                /// @param flags Флаги из списка @link Flags
                /// @param TextColor 
                /// @param BackgroundColor 
                void Set(const char c, const Fonts::Font& font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);

                /// @brief 
                /// @param img
                void Set(const Images::Image &img, const Fonts::Font &size = Fonts::DefaultFont);

                /// @brief Изменить флаги
                /// @param flags 
                void SetFlags(unsigned flags);

                /// @brief Изменить цвет текста
                /// @param NewColor 
                void SetTextColor(const Colors::Color &NewColor);

                /// @brief Изменить цвет фона текста
                /// @param NewColor 
                void SetBackgroundColor(const Colors::Color &NewColor);

                /// @brief Измерить размеры символа
                /// @param size 
                void SetFont(const Fonts::Font& size) const;

                /// @brief Получить ASCII символ
                /// @return 
                char GetChar() const;
                
                /// @brief Получить @link _img
                /// @return 
                const Images::img& GetImg() const;

                /// @brief получить размеры символа
                /// @return 
                const Fonts::Font& GetFont() const;

                /// @brief Получить флаги
                /// @return 
                unsigned GetFlags() const;

                /// @brief Отрисовать
                /// @param coord Координаты
                void Print(const UI::Coord &coord) const;

                Char& operator = (char c);
                Char& operator = (const Images::img &img);
                Char& operator = (const Char &c);

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

                mutable Fonts::Font _font;

/*====================Параметры для текста=================*/
                mutable Colors::Color *_TextColor;
                mutable Colors::Color *_BackgroundColor;
/*=========================================================*/

                /// @brief Тип
                /// @paragraph Хранит значение из спика @link Char::Type
                unsigned _type;
            };
            
            /// @brief Текст
            /// @paragraph Фактически std::vector @link Char ов
            class Text
            {
            public:
                /// @brief Конструктор
                Text();

                /// @brief Деструктор
                ~Text();

                /// @brief Добавить символ в конец
                /// @param c символ
                void Add(const Char& c);

                /// @brief Добавить строку в конец
                /// @param txt строка
                void Add(const std::string& txt);

                /// @brief долбавить изображение в конец
                /// @param img Добавляемое изображение
                void Add(const Images::img& img);

                /// @brief Вставить элемент
                /// @param c Символ
                /// @param i номер
                void insert(const Char& c, int i);

                /// @brief Вставить строку
                /// @param txt строка
                /// @param i номер
                void insert(const std::string &txt, int i);

                /// @brief Вставить изображение
                /// @param img изображение
                /// @param i номер
                void insert(const Images::img &img, int i);

                /// @brief Удалить Char из текста
                /// @param i Номер удаляемого Charа
                void Delete(int i);

                /// @brief Вывести текст
                /// @param coord Координаты(левый верхний угол) текста
                void Print(const UI::Coord &coord) const;

                /// @brief Изменить шрифт символов
                /// @param FontSize 
                /// @paragraph Изменяет размер символов для всех символов
                void SetFont(const Fonts::Font& Font);

                /// @brief Изменить цвет текста для всех символов
                /// @param Color 
                void SetTextColor(const Colors::Color &Color);

                /// @brief Изменить цвет фона для всех символов
                /// @param Color 
                void SetBackgroundColor(const Colors::Color &Color);

                /// @brief Получить текст
                /// @return 
                std::string& GetText() const;

                /// @brief Получить символ под номером i
                /// @param i номер
                /// @return _data[i]
                const Char& GetChar(int i) const;

                /// @brief Получить длину текста
                /// @return длина текста
                std::size_t length() const;

                /// @brief Получить длинну текста в пикселях 
                /// @return 
                unsigned lenghtPX() const;

                /// @brief 
                /// @param text 
                void SetText(std::string text);

                Text& operator = (const Text& txt);

                /// @brief 
                /// @param txt 
                /// @return 
                bool operator == (const Text& txt) const;

            protected:                
                std::vector<Char> _data;
            };
            

            //=============================================================================================================================================================

            /// @brief Текстовая метка
            /// @paragraph Простая текстовая метка, ничего особенного.
            /// @paragraph Возможно важные сведения: текст всегда отрисовывается в середине 
            class TextLabel: public UI::UIElement, public Text
            {
            private:
                /// @brief Выравнивание
                unsigned Align;

                /// @brief (Да/Нет)Подстраивать @link _FontSize, чтобы размер текст соответствовал размеру элемента( @link _size)
                bool _TextScale;

                mutable bool _Aligned;


            public:
                /// @brief Конструктор
                /// @param coord координата
                /// @param size Рамер элемента, игнорируется если TextScale = false
                /// @param text Текст текста
                /// @param FontSize Размер текста
                /// @param TextScale Маштабировать текст, чтобы он не выходил за границы элемента
                /// @param Margin Отступы от границ
                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const unsigned& FontSize = 9, bool TextScale = true, const Colors::Color& TextColor = OS::sys_color_table.work_text, const unsigned& Margin = 0);

                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const Fonts::Font &Font = Fonts::DefaultFont, const Colors::Color& TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.frame_area , bool TextScale = true, const unsigned& Margin = 0);

                ~TextLabel();

                /// @brief Отрисовать текстовую метку
                virtual void Render() const;

                /// @brief Изменить значение переменной @link _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);
                
                /// @brief Получить состояние переменной @link _TextScale
                /// @ return значение переменной @link _TextScale
                bool GetScale() const; 



                /// @brief 
                /// @param a 
                /// @return 
                TextLabel& operator = (const TextLabel& a);

                /// @brief 
                /// @param a 
                /// @return 
                bool operator == (const TextLabel& a) const;

                bool operator != (const TextLabel& a) const;
            };

            
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__