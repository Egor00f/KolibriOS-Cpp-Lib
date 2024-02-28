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
            
            /// @brief Пародия на шрифты
            /// @paragraph На самом деле это не настоящие шрифты, а лишь жалкие пародии, совподающие с настоящими лишь по размерам(ширина/высота)
            namespace Fonts
            {
                const UI::Size Arial = {5,6};
                const
            };

            const UI::Size DefaultTextSize = Fonts::Arial;

            

            /// @brief Вывести текст
            /// @param text Текст
            /// @param coord Координаты текста
            /// @param size Размеры символа(в px)
            /// @param flags Флаги
            /// @param margin Отступы границ фона от текста
            /// @param colorText Цвет текста
            /// @param BackgroundColor Цвет фона текста
            /// @paragraph Функция выводит текст, и фон текста
            /// @example DrawText("Text", {0,0}, Fonts::Arial*16); //16 - высота шрифта
            void DrawText(const std::string &text, 
                const Coord &coord, const Size &size = DefaultTextSize, 
                unsigned flags = Flags::Normal, 
                unsigned margin = UI::DefaultMargin,
                const Colors::Color &colorText = OS::sys_color_table.work_text, 
                const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);

            

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
                Char(char c = ' ', const UI::Size &size = DefaultTextSize, const unsigned flags = Flags::Normal, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);

                /// @brief Конструктор
                /// @param img изображение
                Char(const Images::img& img, const UI::Size& size = DefaultTextSize);

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
                void Set(const char c, const UI::Size &size, const unsigned flags = 0, const Colors::Color &TextColor = OS::sys_color_table.work_text, const Colors::Color &BackgroundColor = OS::sys_color_table.work_area);

                /// @brief 
                /// @param img
                void Set(const Images::Image &img, const UI::Size &size = DefaultTextSize);

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
                void SetSize(const UI::Size& size) const;

                /// @brief Получить ASCII символ
                /// @return 
                char GetChar() const;
                
                const Images::img& GetImg() const;

                /// @brief получить размеры символа
                /// @return 
                const UI::Size& GetSize() const;

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
                union 
                {
                    Images::img *_img;
                    char *_c;
                };
                

            private:
                /// @brief Освободить все переменные
                void Free();

/*====================Параметры для текста=================*/
                mutable UI::Size *_size;
                mutable Colors::Color *_TextColor;
                mutable Colors::Color *_BackgroundColor;
                mutable unsigned *_flags;
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

                /// @brief 
                /// @param i 
                void Delete(int i);

                /// @brief Вывести текст
                /// @param coord Координаты(левый верхний угол) текста
                void Print(const UI::Coord &coord) const;

                /// @brief Изменить размер символов
                /// @param FontSize 
                /// @paragraph Изменяет размер символов для всех символов
                void SetSize(UI::Size FontSize);

                /// @brief Получить длину текста
                /// @return длина текста
                std::size_t length() const;

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
            class TextLabel : public UI::UIElement, public Text
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

                ~TextLabel();

                /// @brief Отрисовать текстовую метку
                void Render() const;

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