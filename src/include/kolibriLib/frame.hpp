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
            Frame(const Coord &coord = {0,0}, const Size &size = {0,0}, const Color::Color &Color = OS::sys_color_table.work_area, const unsigned &Margin = DefaultMargin);
            

            /// @brief Отрисовать фрейм
            void Render();

            void Handler();

            template <class T>
            /// @brief Добавить элемент во фрейм
            /// @param element элемент
            /// @return номер 
            unsigned AddElement(const T &element);
        };
        Frame::Frame(const Coord &coord, const Size &size, const Color::Color &Color, const unsigned &Margin) : UIElement(coord, size, Color, Margin)
        {
            #if DEBUG == true
            _ksys_debug_puts("Frame constructor\n");
            #endif
        }

        void UI::Frame::Render()
        {
            graphic::DrawRectangleFill(_coord, _size, _MainColor);

            for (unsigned i = 0; i < _Elements.size(); i++)
            {
                if (_Elements[i].use)
            {   
                switch (_Elements[i]._type)
                {
                case Element::Type::TextLabel:
                    _Elements[i].txt.Render();
                    break;
                case Element::Type::Button:
                    _Elements[i].btn.Render();
                    break;
                case Element::Type::Image:
                    _Elements[i].img.Render();
                    break;
                case Element::Type::Form:
                    _Elements[i].frm.Render();
                    break;
                case Element::Type::CheckBox:
                    _Elements[i].ChckBx.Render();
                default:
                    break;
                }
            }
        }
    }

    void UI::Frame::Handler()
    {
        if (Hover())
        {

        }
    }

    template <class T>
    unsigned UI::Frame::AddElement(const T &element)
    {
        /* UI::Element a;

        switch (T)
        {
        case text::TextLabel:
            a.txt   = element;
            a._type = Element::Type::TextLabel;
            break;
        case buttons::Button:
            a.btn   = element;
            a._type = Element::Type::Button;
            break;
        case Images::Image:
            a.img   = element;
            a._type = Element::Type::Image;
            break;
        case Form:
            a.frm   = element;
            a._type = Element::Type::Form;
            break;
        case CheckBox:
            a.ChckBx    = element;
            a._type     = Element::Type::CheckBox;
            break;
        default:
            break;
        }
        a.use = true;

        for(unsigned i = 0; i < _Elements.size(); i++)  //Ищем свободный элемент
        {
            if(!_Elements[i].use)
            {
                _Elements[i] = a;
                return i;
            }
        }


        _Elements.push_back(a);
        */

        return _Elements.size() - 1;
    }
    } // namespace UI
} // namespace KolibriLib


#endif // __FRAME_H__