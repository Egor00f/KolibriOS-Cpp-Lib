#include "frame.hpp"



using namespace KolibriLib;
using namespace UI;

Frame::Element::Element()
{
    #if DEBUG == true
    _ksys_debug_puts("KolibriLib::Frame::Element constructor\n");
    #endif
    _type = Type::None;
}

Frame::Element::~Element()
{
    #if DEBUG == true
    _ksys_debug_puts("KolibriLib::Frame::Element destructor\n");
    #endif
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
void Frame::Element::SetElement(const T& elem)
{
    _ksys_debug_puts("Error in KolibriLib::UI::Frame::Element::SetElement: unklown type");
}

//=============================================================================================================================================================
template <>
void Frame::Element::SetElement<UI::buttons::Button>(const UI::buttons::Button& elem)
{
    free();
    btn = new UI::buttons::Button(elem);
    _type = Type::Button;
}

template <>
void Frame::Element::SetElement<UI::Images::Image>(const UI::Images::Image& elem)
{
    free();
    img = new UI::Images::Image(elem);
    _type = Type::Image;
}

template <>
void Frame::Element::SetElement<UI::CheckBox>(const UI::CheckBox& elem)
{
    free();
    checkbox = new UI::CheckBox(elem);
    _type = Type::CheckBox;
}

template <>
void Frame::Element::SetElement<UI::Form>(const UI::Form& elem)
{
    free();
    form = new UI::Form(elem);
    _type = Type::Form;
}

template <>
void Frame::Element::SetElement<UI::text::TextLabel>(const UI::text::TextLabel& elem)
{
    free();
    txt = new UI::text::TextLabel(elem);
    _type = Type::TextLabel;
}

template <>
void Frame::Element::SetElement<UI::Menu>(const UI::Menu& elem)
{
    free();
    menu = new UI::Menu(elem);
    _type = Type::Menu;
}

Frame::Frame(const Coord &coord, const Size &size, const Colors::Color &Color, const unsigned &Margin) : UIElement(coord, size, Color, Margin)
{
    #if DEBUG == true
    _ksys_debug_puts("Frame constructor\n");
    #endif
}

void UI::Frame::Render()
{
    graphic::DrawRectangleFill(_coord, _size, _MainColor);

    for (const std::pair<int, Element> &n : _Elements)
    {
        switch (n.second._type)
        {
        case Element::Type::TextLabel:
            n.second.txt->Render();
            break;
        case Element::Type::Button:
            n.second.btn->Render();
            break;
        case Element::Type::Image:
            n.second.img->Render();
            break;
        case Element::Type::Form:
            n.second.form->Render();
            break;
        case Element::Type::CheckBox:
            n.second.checkbox->Render();
            break;
        case Element::Type::Menu:
            n.second.menu->Render();
            break;
        default:
            break;
        }
    }
}

void UI::Frame::Handler()
{
    if (Hover())
    {
        
    }
}

void KolibriLib::UI::Frame::DeleteElement(int i)
{
    if(_Elements.count(i)) //Проверка что элемент с таким ключом
    {
        _Elements.erase(i);
    }
    _ksys_debug_puts("KolibriLib::UI::Frame::DeleteElement: \n");
}

template <class T>
unsigned UI::Frame::AddElement(const T &element)
{
    Element a;
    a.SetElement(element);

    auto p = _Elements.emplace(a);
    return p.first;
    
    _ksys_debug_puts("KolibriLib::UI::Frame::AddElement _Elements is overflow\n");
}
template <class T>
void UI::Frame::SetElement(int i, const T &element)
{
    if (_Elements.count(i))
    {
        _Elements[i].SetElement(element);
        return;
    }
    _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
}

const Frame::Element& UI::Frame::GetElement(int i) const
{
    if (_Elements.count(i))
    {
        return _Elements.at(i);
    }
    _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
}