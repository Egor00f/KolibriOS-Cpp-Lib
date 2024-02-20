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

    if(_maxElement == 0)
    {
        return;
    }

    int* i = new int(0);
    do
    {
        switch (_Elements[*i]._type)
        {
        case Element::Type::TextLabel:
            _Elements[*i].txt->Render();
            break;
        case Element::Type::Button:
            _Elements[*i].btn->Render();
            break;
        case Element::Type::Image:
            _Elements[*i].img->Render();
            break;
        case Element::Type::Form:
            _Elements[*i].form->Render();
            break;
        case Element::Type::CheckBox:
            _Elements[*i].checkbox->Render();
            break;
        case Element::Type::Menu:
            _Elements[*i].menu->Render();
            break;
        default:
            break;
        }
        *i++;
    }while(*i < _maxElement);
    delete i;
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
}

template <class T>
unsigned UI::Frame::AddElement(const T &element)
{
    for (unsigned i = 0; i < _Elements.max_size(); i++)
    {
        if (_Elements.count(i) == 0)    //Если элемента с таким ключём не существует
        {
            _Elements[i].SetElement(element);
            if(i > _maxElement)
            {
                _maxElement = i;
            }
            return i;
        }
    }
    
    _ksys_debug_puts("KolibriLib::UI::Frame::_Elements is overflow\n");
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

const Frame::Element& UI::Frame::GetElement(int i)
{
    if (_Elements.count(i))
    {
        return _Elements[i];
    }
    _ksys_debug_puts("KolibriLib::UI::Frame::Element::SetElement: i >= _Elements.size(), return\n");
}