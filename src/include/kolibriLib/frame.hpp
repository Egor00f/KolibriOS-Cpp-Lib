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

namespace KolibriLib
{
    namespace UI
    {
        
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
        

        class Frame: public UIElement
        {
        private:
            std::vector<Element> _Elements;
            bool _scroll;
        public:
            Frame(const Coord &coord = {0,0}, const Size &size = {0,0}, const Color::Color &Color = OS::sys_color_table.work_area, const unsigned &Margin = DefaultMargin);
            ~Frame();

            /// @brief Отрисовать фрейм
            void Render();

            void Handler();

            template <class T>
            void AddElement(const T &element);
        };

    } // namespace UI
    
} // namespace KolibriLib


#endif // __FRAME_H__