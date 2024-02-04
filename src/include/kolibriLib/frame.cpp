#include "frame.hpp"

using namespace KolibriLib;

UI::Frame::Frame(const Coord &coord, const Size &size, const Color::Color &Color, const unsigned &Margin) : UIElement(coord, size, Color, Margin)
{

}

void UI::Frame::Render()
{
    graphic::DrawRectangleFill(_coord, _size, _MainColor);

    for (unsigned i = 0; i < _Elements.size(); i++)
    {
        if (!_Elements[i].use)
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
    if(Hover())
    {
        
    }
}

template <class T>
void UI::Frame::AddElement(const T &element)
{
    UI::Element a;

    if(std::is_same<>)

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
}