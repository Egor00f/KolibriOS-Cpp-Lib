#ifndef __FRAME_H__
#define __FRAME_H__


#include <vector>
#include <type_traits>

#include "graphic.hpp"
#include "UI.hpp"
#include "text.hpp"
#include "button.hpp"
#include "form.hpp"
#include "image.hpp"
#include "checkbox.hpp"
#include "input.hpp"

namespace KolibriLib
{
    namespace UI
    {

        class Frame: public UIElement
        {
        private:
            struct Element
            {
                enum Type
                {
                    None = 0,
                    Button,
                    Image,
                    CheckBox,
                    Form,
                    TextLabel
                };

                UI::buttons::Button btn;
                UI::text::TextLabel txt;
                UI::Form frm;
                UI::CheckBox ChckBx;
                UI::Images::Image img;

                unsigned _type;
                bool use;
            };
            std::vector<Element> _Elements;
            bool _scroll;
        public:
            Frame(const Coord &coord = {0,0}, const Size &size = {0,0}, const Colors::Color &Color = OS::sys_color_table.work_area, const unsigned &Margin = DefaultMargin);
            

            /// @brief Отрисовать фрейм
            void Render();

            /// @brief 
            void Handler();

            template <class T>
            /// @brief Добавить элемент во фрейм
            /// @param element элемент
            /// @return номер 
            unsigned AddElement(const T &element);
        };
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__