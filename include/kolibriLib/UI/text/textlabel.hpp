#ifndef __TEXT_LABEL_H__
#define __TEXT_LABEL_H__


#include <sys/ksys.h>

#include <string>

#include <kolibriLib/types.hpp>
#include <kolibriLib/UI/UI.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/graphic/graphic.hpp>
#include <kolibriLib/window/windowBase.hpp>
#include <kolibriLib/UI/image.hpp>
#include <kolibriLib/UI/text/text.hpp>
//#include "font.hpp"
//#include "fontslist.hpp"

//#include <kolibri_rasterworks.h>

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
            /// @example example.cpp
            class TextLabel: public Txt, public UI::UIElement
            {
            public:

                /// @brief Выравнивание текста в метке
                enum class Align
                {
                    /// @brief Выравнивание по правому ккраю
                    /// @details текст прижимается к правой стороне
                    Right,

                    /// @brief Выравнивание по левому ккраю
                    /// @details Текст прижат к левой стороне
                    Left,

                    /// @brief Выравнивание по центру
                    /// @details Текст по центру
                    Center
                };

                /// @brief Конструктор
                /// @param coord координата
                /// @param size Рамер элемента, игнорируется если TextScale = false
                /// @param text Текст текста
                /// @param FontSize Размер текста
                /// @param TextScale Маштабировать текст, чтобы он не выходил за границы элемента
                /// @param Margin Отступы от границ
                TextLabel(const UDim& coord = point(0), const UDim& size = DefaultSize, const std::string& text = "TextLabel", const Size &CharSize = {8, 16}, bool TextScale = true, const Colors::Color& TextColor = Globals::SystemColors.work_text, const unsigned& Margin = 0);

                /// @brief Коснтруктор
                /// @param coord коорднаты
                /// @param size размер
                /// @param text текст
                /// @param Font шрифт
                /// @param TextColor цвет текста
                /// @param BackgroundColor цвет фона
                /// @param TextScale 
                /// @param Margin
                // TextLabel(const UDim &coord = point(0), const UDim &size = DefaultSize, const std::string &text = "TextLabel",/* const Fonts::Font &Font = Fonts::DefaultFont,*/ const Colors::Color &TextColor = OS::GetSystemColors().gui_text, const Colors::Color &BackgroundColor = OS::GetSystemColors().gui_frame, bool TextScale = true, unsigned Margin = 0);
                
                /// @brief конструктор
                /// @param coord коордирдинаты
                /// @param size размер
                /// @param text текст
                TextLabel(const UDim &coord = point(0), const UDim &size = DefaultSize, const Txt &text = Txt());

                /// @brief Конструктор копирования
                /// @param copy объекто который будет копироваться
                TextLabel(const TextLabel &copy);

                /// @brief Отрисовать текстовую метку
                void Render() const override;

                /// @brief Изменить значение переменной _TextScale
                /// @param scale Новое значение
                void SetScale(bool scale);
                
                /// @brief Получить состояние переменной _TextScale
                /// @ return значение переменной _TextScale
                bool GetScale() const; 

                /// @brief Изменить выравнивание
                /// @param aling 
                void SetAling(TextLabel::Align aling);

                /// @brief получить выравнивание
                /// @return 
                Align GetAling() const;

                /// @brief 
                /// @param a 
                /// @return 
                TextLabel& operator = (const TextLabel& a) = default;

                /// @brief 
                /// @param a 
                /// @return 
                bool operator == (const TextLabel& a) const;

                bool operator != (const TextLabel& a) const;
                
                /// @brief 
                /// @param a 
                void swap(TextLabel& a);
            private:
                /// @brief Выравнивание
                Align _Align = Align::Center;

                /// @brief (Да/Нет)Подстраивать _FontSize, чтобы размер текст соответствовал размеру элемента(_size)
                /// @warning пока что не работает
                bool _TextScale;

                mutable bool _Aligned;
            };
        }
    } // namespace UI
    

    void PrintDebug(const UI::text::TextLabel &out);
} // namespace KolibriLib


#endif // __TEXT_H__