#include "frame.hpp"



using namespace KolibriLib;
using namespace UI;

Frame::Frame(const Coord &coord, const Size &size, const Colors::Color &Color, const unsigned &Margin) : UIElement(coord, size, Color, Margin)
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
                _Elements[i].txt->Render();
                break;
            case Element::Type::Button:
                _Elements[i].btn->Render();
                break;
            case Element::Type::Image:
                _Elements[i].img->Render();
                break;
            case Element::Type::Form:
                _Elements[i].form->Render();
                break;
            case Element::Type::CheckBox:
                _Elements[i].checkbox->Render();
            case Element::Type::Menu:
                _Elements[i].menu->Render();
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

void KolibriLib::UI::Frame::DeleteElement(unsigned i)
{
    _Elements[i].use = false;
}

template <class T>
unsigned UI::Frame::AddElement(const T &element)
{
    Element a;

    a.SetElement(element);

    a.use = true;

    for (unsigned i = 0; i < _Elements.size(); i++) // Ищем свободный элемент
    {
        if (!_Elements[i].use)
        {
            _Elements[i] = a;
            return i;
        }
    }

    _Elements.push_back(a);

    return _Elements.size() - 1;
}

template <class T>
void UI::Frame::SetElement(unsigned i, const T &element)
{
    if (i >= _Elements.size())
    {
        _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        return;
    }
    _Elements[i].SetElement(element);
}

template <class T>
T UI::Frame::GetElement(unsigned i) const
{
    if (i >= _Elements.size())
    {
        _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
        return 0;
    }

    switch (_Elements[i]._type)
    {
    case Element::Type::TextLabel:
        return _Elements[i].txt;
    case Element::Type::Button:
        return _Elements[i].btn;
    case Element::Type::Image:
        return _Elements[i].img;
    case Element::Type::Form:
        return _Elements[i].form;
    case Element::Type::CheckBox:
        return _Elements[i].checkbox;
    default:
        _ksys_debug_puts("KolibriLib::UI::Frame::Element::GetElement: unknown type, break\n");
        break;
    }
    return 0;
}

Frame::Element::Element()
{
    use = false;
    _type = Type::None;
}

Frame::Element::~Element()
{
    free();
}

void Frame::Element::free()
{
    switch (_type)
    {
    case Type::Button:
        delete btn;
        break;
    case Type::Image:
        delete img;
        break;
    case Type::CheckBox:
        delete checkbox;
        break;
    case Type::Form:
        delete form;
        break;
    case Type::TextLabel:
        delete txt;
        break;
    case Type::Menu:
        delete menu;
        break;
    default:
        break;
    }
}

template <class T>
void Frame::Element::SetElement(const T &elem)
{
    _ksys_debug_puts("Error in KolibriLib::UI::Frame::Element::SetElement: unklown type");
}

//=============================================================================================================================================================
template <>
void Frame::Element::SetElement<UI::buttons::Button>(const UI::buttons::Button &elem)
{
    free();
    btn = new UI::buttons::Button(elem);
    _type = Type::Button;
}

template <>
void Frame::Element::SetElement<UI::Images::Image>(const UI::Images::Image &elem)
{
    free();
    img = new UI::Images::Image(elem);
    _type = Type::Image;
}

template <>
void Frame::Element::SetElement<UI::CheckBox>(const UI::CheckBox &elem)
{
    free();
    checkbox = new UI::CheckBox(elem);
    _type = Type::CheckBox;
}

template <>
void Frame::Element::SetElement<UI::Form>(const UI::Form &elem)
{
    free();
    form = new UI::Form(elem);
    _type = Type::Form;
}

template <>
void Frame::Element::SetElement<UI::text::TextLabel>(const UI::text::TextLabel &elem)
{
    free();
    txt = new UI::text::TextLabel(elem);
    _type = Type::TextLabel;
}

template <>
void Frame::Element::SetElement<UI::Menu>(const UI::Menu &elem)
{
    free();
    menu = new UI::Menu(elem);
    _type = Type::Menu;
}
