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
#include "font.hpp"
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
                /// @warning пока что не работает
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

                /// @brief 
                /// @param coord 
                /// @param size
                /// @param text 
                TextLabel(const Coord &coord = {0,0}, const Size size = {16, 16}, const Txt &text = Txt());

                /// @brief Конструктор копирования
                /// @param copy объекто который будет копироваться
                TextLabel(const TextLabel &copy);

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
        }
    } // namespace UI
    
} // namespace KolibriLib


#endif // __TEXT_H__