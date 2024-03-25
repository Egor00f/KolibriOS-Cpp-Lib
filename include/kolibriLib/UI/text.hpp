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
#include "textBase.hpp"

namespace KolibriLib
{
    namespace UI
    {
        /// @brief Работа с тектсом
        namespace text
        {
            

            /// @brief Символ
            /// @note Символ который может содержать как текст, так и картинку(например смайлик)
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
                Char(char c = ' ', const Fonts::Font& font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

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
                void Set(const char c, const Fonts::Font& font = Fonts::DefaultFont, const Colors::Color &TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area);

                /// @brief 
                /// @param img
                void Set(const Images::Image &img, const Fonts::Font &size = Fonts::DefaultFont);

                /// @brief Изменить флаги
                /// @param flags 
                void SetFlags(unsigned flags);

                /// @brief Изменить цвет текста
                /// @param NewColor новый цвет фона
                void SetTextColor(const Colors::Color &NewColor);

                /// @brief Изменить цвет фона текста
                /// @param NewColor новый цвет фона
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
                void Print(const Coord &coord) const;

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

                /// @brief Конструктор
                /// @param text
                Text( const std::string& text);

                

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
                void Print(const Coord &coord) const;

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
                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const unsigned& FontSize = 9, bool TextScale = true, const Colors::Color& TextColor = OS::GetSystemColors().work_text, const unsigned& Margin = 0);

                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const Fonts::Font &Font = Fonts::DefaultFont, const Colors::Color& TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().frame_area , bool TextScale = true, const unsigned& Margin = 0);

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

            KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(char c)
            {
                if (_type == Char::Type::Text)
                {
                    *_c = c;
                }
                else
                {
                    Free();
                    _c = new char(c);
                    _font = Fonts::DefaultFont;
                    _TextColor = new Colors::Color(OS::GetSystemColors().work_text);
                    _BackgroundColor = new Colors::Color(OS::GetSystemColors().work_area);
                    _type = Type::Text;
                }
            }

            KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(const KolibriLib::UI::text::Char &c)
            {
                Free();
                _font = c._font;

                switch (c._type)
                {
                case Char::Type::Text:
                    _c = new char(*c._c);
                    _TextColor = new Colors::Color(c._TextColor->val);
                    _BackgroundColor = new Colors::Color(c._BackgroundColor->val);
                    _type = Type::Text;
                    break;
                case Char::Type::Image:

                    _img = new Images::img(*c._img);
                    _type = Type::Image;

                    break;
                default:
                    break;
                }
            }

            bool Char::operator==(const Char &img) const
            {
                return (_type == img._type) &&
                       (_font == img._font);
            }

            TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) : UIElement(coord, size, TextColor, Margin)
            {
                Add(text);
                _TextScale = TextScale;
            }

            TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const UI::text::Fonts::Font &Font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, bool TextScale, const unsigned &Margin)
            {
                _ksys_debug_puts("TextLabel Constructor\n");
                Add(text);
                _TextScale = TextScale;
                SetFont(Font);
            }

            text::TextLabel::~TextLabel()
            {
            }

            void text::TextLabel::Render() const
            {
                unsigned *FontSize = new unsigned;
                *FontSize = 0;
                if (_TextScale) // Если текст нужно подстраивать размер, то
                {               // Постраиваем
                    *FontSize = _size.x / lenghtPX();
                    if (!_Aligned)
                    {
                        for (int i = 0; i < _data.size(); i++)
                        {
                            Fonts::Font buff = _data[i].GetFont();
                            _data[i].SetFont(Fonts::Font(buff._Font, *FontSize, buff._Flags));
                        }
                        _Aligned = true;
                    }
                }
                delete FontSize;
                Print({_coord.x + ((int)_size.x / 2), _coord.y + ((int)_size.y / 2)});
            }

            void text::TextLabel::SetScale(bool scale)
            {
                _TextScale = scale;
            }

			bool TextLabel::GetScale() const
			{
				return _TextScale;
			}

			text::TextLabel &KolibriLib::UI::text::TextLabel::operator=(const KolibriLib::UI::text::TextLabel &a)
            {
                _coord = a._coord;
                _size = a._size;
                _MainColor = a._MainColor;
                _Margin = a._Margin;
                _TextScale = a._TextScale;
                return *this;
            }

            bool KolibriLib::UI::text::TextLabel::operator==(const KolibriLib::UI::text::TextLabel &a) const
            {
                return (_coord == a._coord) &&
                       (_size == a._size) &&
                       (_MainColor == a._MainColor) &&
                       (_Margin == a._Margin) &&
                       (_TextScale == a._TextScale);
            }

            bool KolibriLib::UI::text::TextLabel::operator!=(const KolibriLib::UI::text::TextLabel &a) const
            {
                return (_coord == a._coord) ||
                       (_size == a._size) ||
                       (_MainColor == a._MainColor) ||
                       (_Margin == a._Margin) ||
                       (_TextScale == a._TextScale);
            }

            KolibriLib::UI::text::Char::Char(char c, const KolibriLib::UI::text::Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
            {
                _ksys_debug_puts("Char consturctor\n");
                _c = new char(c);
                _font = font;
                _TextColor = new Colors::Color(TextColor);
                _BackgroundColor = new Colors::Color(BackgroundColor);
                _type = Type::Text;
            }

            KolibriLib::UI::text::Char::Char(const Images::img &img, const KolibriLib::UI::text::Fonts::Font &font)
            {
                _ksys_debug_puts("Char constructor\n");
                _img = new Images::img(img);
                _font = font;
                _type = Type::Image;
            }

            KolibriLib::UI::text::Char::~Char()
            {
                Char::Free();
            }

            short KolibriLib::UI::text::Char::GetType() const
            {
                return _type;
            }

            void KolibriLib::UI::text::Char::Set(const char c, const Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
            {
                Char::Free(); // Пофиг какой раньше тип был, просто тупо сносим и делаем всё заново
                _font = font;
                _TextColor = new Colors::Color(TextColor);
                _BackgroundColor = new Colors::Color(BackgroundColor);
                _c = new char(c);
                _type = Type::Text;
            }

            void KolibriLib::UI::text::Char::Set(const Images::Image &img, const KolibriLib::UI::text::Fonts::Font &size)
            {
                Char::Free();
                _img = new Images::Image(img);
                _font = size;
                _type = Type::Image;
            }

            void KolibriLib::UI::text::Char::SetFlags(unsigned flags)
            {
                assert(_type == Type::Text);
                _font._Flags = flags;
            }

            void KolibriLib::UI::text::Char::SetTextColor(const Colors::Color &NewColor)
            {
                assert(_type == Type::Text);
                *_TextColor = NewColor.val;
            }

            void KolibriLib::UI::text::Char::SetBackgroundColor(const Colors::Color &NewColor)
            {
                assert(_type == Type::Text);
                *_BackgroundColor = NewColor.val;
            }

            void KolibriLib::UI::text::Char::SetFont(const KolibriLib::UI::text::Fonts::Font &newFont) const
            {
                assert(_type == Type::Text);
                _font = newFont;
            }

            char KolibriLib::UI::text::Char::GetChar() const
            {
                assert(_type == Type::Text);
                return *_c;
            }

            const Images::img &KolibriLib::UI::text::Char::GetImg() const
            {
                assert(_type == Type::Image);
                return *_img;
            }

            const Fonts::Font &KolibriLib::UI::text::Char::GetFont() const
            {
                assert(_type == Type::None);
                return _font;
            }

            unsigned KolibriLib::UI::text::Char::GetFlags() const
            {
                assert(_type == Type::Text);
                return _font._Flags;
            }

            void KolibriLib::UI::text::Char::Free()
            {
                switch (_type)
                {
                case Type::Image:
                    delete _img;
                    break;
                case Type::Text:
                    delete _c;
                    delete _TextColor;
                    delete _BackgroundColor;
                    break;
                default:
                    break;
                }
            }

            void KolibriLib::UI::text::Char::Print(const Coord &coord) const
            {
                switch (_type)
                {
                case Type::Image:
                    _img->Render(coord, _font.size);
                    break;
                case Type::Text:
                    DrawText(std::string(_c), coord, _font, OS::GetSystemColors().work_text, *_TextColor, *_BackgroundColor);
                    break;
                default:
                    break;
                }
            }

            std::string &KolibriLib::UI::text::Text::GetText() const
            {
                std::string result;
                for (int i = 0; i < _data.size(); i++)
                {
                    if (_data[i].GetType() == Char::Type::Text)
                    {
                        result += _data[i].GetChar();
                    }
                }
                return result;
            }

            const Char &Text::GetChar(int i) const
            {
                return _data.at(i);
            }

			Text::Text()
			{
                _ksys_debug_puts("Text constructor\n");
			}

			Text::Text(const std::string &text)
			{
                _ksys_debug_puts("Text constructor\n");
                SetText(text);
			}

			void KolibriLib::UI::text::Text::Add(const KolibriLib::UI::text::Char &c)
			{
                _data.push_back(c);
            }

            void KolibriLib::UI::text::Text::Add(const std::string &txt)
            {
                if (_data.size() == 0)
                {
                    _data.push_back(Char(txt[0])); // На случай если вектор пустой
                }
                for (int i = 1; i < txt.length(); i++)
                {
                    _data.push_back(Char(txt[i]));
                }
            }

            void KolibriLib::UI::text::Text::Add(const Images::img &img)
            {
                _data.push_back(Char(img));
            }
            void KolibriLib::UI::text::Text::insert(const KolibriLib::UI::text::Char &c, int i)
            {
                _data.insert(_data.begin() + i, c);
            }

            void KolibriLib::UI::text::Text::insert(const std::string &txt, int i)
            {
                for (int j = txt.length(); j > 0; j++)
                {
                    _data.insert(_data.begin() + i, Char(txt[j], _data[i].GetFont()));
                }
            }

            void KolibriLib::UI::text::Text::insert(const Images::img &img, int i)
            {
                _data.insert(_data.begin() + i, Char(img));
            }

            void KolibriLib::UI::text::Text::Delete(int i)
            {
                _data.erase(_data.begin() + i);
            }

            void KolibriLib::UI::text::Text::Print(const Coord &coord) const
            {
                int buff = 0;
                for (int i = 0; i < _data.size(); i++)
                {
                    _data[i].Print({coord.x + buff, coord.y});
                    buff += _data[i].GetFont().size.x;
                }
            }

            void KolibriLib::UI::text::Text::SetFont(const Fonts::Font &Font)
            {
                for (int i = 0; i < _data.size(); i++)
                {
                    _data[i].SetFont(Font);
                }
            }

            void KolibriLib::UI::text::Text::SetTextColor(const Colors::Color &Color)
            {
                for (int i = 0; i < _data.size(); i++)
                {
                    if (_data[i].GetType() == Char::Type::Text)
                    {
                        _data[i].SetTextColor(Color);
                    }
                }
            }

            void KolibriLib::UI::text::Text::SetBackgroundColor(const Colors::Color &Color)
            {
                for (int i = 0; i < _data.size(); i++)
                {
                    if (_data[i].GetType() == Char::Type::Text)
                    {
                        _data[i].SetBackgroundColor(Color);
                    }
                }
            }

            bool KolibriLib::UI::text::Text::operator==(const KolibriLib::UI::text::Text &txt) const
            {
                return _data == txt._data;
            }

            std::size_t KolibriLib::UI::text::Text::length() const
            {
                return _data.size();
            }

            unsigned KolibriLib::UI::text::Text::lenghtPX() const
            {
                unsigned l = 0;
                for (unsigned i = 0; i < _data.size(); i++)
                {
                    l += _data[i].GetFont().size.x;
                }
                return l;
            }

            void KolibriLib::UI::text::Text::SetText(std::string text)
            {
                for (std::size_t i = 0; i < text.length(); i++)
                {
                    _data[i].Set(text[i], _data[i].GetFont());
                }
            }

            KolibriLib::UI::text::Text &KolibriLib::UI::text::Text::operator=(const Text &txt)
            {
                _data = txt._data;
                return *this;
            }
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__