#ifndef __TEXT_LABEL_H__
#define __TEXT_LABEL_H__


#include <sys/ksys.h>

#include <string>
#include <assert.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibriLib/UI/text/text.hpp>
#include "fonts.hpp"
#include "fontslist.hpp"

#include <kolibri_rasterworks.h>

namespace KolibriLib
{
    namespace UI
    {

        /// @brief Работа с тектсом
        namespace text
        {
            /// @brief Текстовая метка
            /// @note Простая текстовая метка, ничего особенного.
            /// @note Возможно важные сведения: текст всегда отрисовывается в середине 
            class TextLabel: public Txt, public UI::UIElement
            {
            private:
                /// @brief Выравнивание
                unsigned Align;

                /// @brief (Да/Нет)Подстраивать _FontSize, чтобы размер текст соответствовал размеру элемента(_size)
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

                /// @brief Коснтруктор
                /// @param coord коорднаты
                /// @param size размер
                /// @param text текст
                /// @param Font шрифт
                /// @param TextColor цвет текста
                /// @param BackgroundColor цвет фона
                /// @param TextScale 
                /// @param Margin 
                TextLabel(const Coord& coord = {0, 0}, const Size& size = {16, 16}, const std::string& text = "TextLabel", const Fonts::Font &Font = Fonts::DefaultFont, const Colors::Color& TextColor = OS::GetSystemColors().work_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().work_area , bool TextScale = true, unsigned Margin = 0);

                /// @brief Отрисовать текстовую метку
                virtual void Render() const;

                /// @brief Изменить значение переменной _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);
                
                /// @brief Получить состояние переменной _TextScale
                /// @ return значение переменной _TextScale
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

            TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) : UIElement(coord, size, TextColor, Margin), Txt(text)
            {
#ifdef DEBUG
                _ksys_debug_puts("TextLabel Constructor\n");
#endif

                Fonts::Font f(Fonts::DefaultFont);
                f.SetFontSize(FontSize);
                SetFont(f);
                f.~Font();

                _TextScale = TextScale;
            }

            TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const UI::text::Fonts::Font &Font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor, bool TextScale, unsigned Margin) : UIElement(coord, size, TextColor, Margin), Txt(text)
            {
#ifdef DEBUG
                _ksys_debug_puts("TextLabel Constructor\n");
#endif
                _TextScale = TextScale;
                SetFont(Font);
            }

            void text::TextLabel::Render() const
            {
                #ifdef DEBUG
                _ksys_debug_puts("Render textLabel:");
                #endif
                unsigned *FontSize = new unsigned;
                *FontSize = 0;
                if (_TextScale) // Если текст нужно подстраивать размер, то
                {               // Постраиваем
                    #ifdef DEBUG
                    _ksys_debug_puts("ScaleText:");
                    #endif
                    // Программа сдесь крашится
                    // *FontSize = _size.x / lenghtPX();
                    // if (!_Aligned)
                    // {
                    //     for (int i = 0; i < _data.size(); i++)
                    //     {
                    //         Fonts::Font buff = _data[i].GetFont();
                    //         _data[i].SetFont(Fonts::Font(buff._Font, *FontSize, buff._Flags));
                    //     }
                    //     _Aligned = true;
                    // }
                    #ifdef DEBUG
                    _ksys_debug_puts("done\n");
                    #endif
                }
                delete FontSize;
                Print(Coord(_coord.x + (_size.x / 2), _coord.y + (_size.y / 2)));
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
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__