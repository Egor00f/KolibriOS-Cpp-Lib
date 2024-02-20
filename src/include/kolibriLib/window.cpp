#include "window.hpp"

using namespace KolibriLib;
using namespace UI;
using namespace window;

Window::Element::Element()
{
    #if DEBUG == true
    _ksys_debug_puts("KolibriLib::window::Window::Element constructor\n");
    #endif
	_type = Type::None;
}

Window::Element::~Element()
{
	free();
}

void Window::Element::free()
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
    case Type::Frame:
        delete frame;
        break;
    default:
        break;
    }
}

template <class T>
void Window::Element::SetElement(const T& elem)
{
    _ksys_debug_puts("Error in KolibriLib::window::Window::Element::SetElement: unklown type");
}

//=============================================================================================================================================================
template <>
void Window::Element::SetElement<UI::buttons::Button>(const UI::buttons::Button& elem)
{
    free();
    btn = new UI::buttons::Button(elem);
    _type = Type::Button;
}

template <>
void Window::Element::SetElement<UI::Images::Image>(const UI::Images::Image& elem)
{
    free();
    img = new UI::Images::Image(elem);
    _type = Type::Image;
}

template <>
void Window::Element::SetElement<UI::CheckBox>(const UI::CheckBox& elem)
{
    free();
    checkbox = new UI::CheckBox(elem);
    _type = Type::CheckBox;
}

template <>
void Window::Element::SetElement<UI::Form>(const UI::Form& elem)
{
    free();
    form = new UI::Form(elem);
    _type = Type::Form;
}

template <>
void Window::Element::SetElement<UI::text::TextLabel>(const UI::text::TextLabel& elem)
{
    free();
    txt = new UI::text::TextLabel(elem);
    _type = Type::TextLabel;
}

template <>
void Window::Element::SetElement<UI::Menu>(const UI::Menu& elem)
{
    free();
    menu = new UI::Menu(elem);
    _type = Type::Menu;
}

template <>
void Window::Element::SetElement<UI::Frame>(const UI::Frame& elem)
{
    free();
    frame = new UI::Frame(elem);
    _type = Type::Frame;
}

//=============================================================================================================================================================


Window::Window(const std::string &Title, const UI::Size &size, const Colors::ColorsTable &colors, const Colors::Color &TitleColor, bool Resize, bool RealtimeRedraw, bool Gradient, unsigned Transparency, const unsigned &Margin)
{
    #if DEBUG == true
    _ksys_debug_puts("KolibriLib::window:::Window constructor\n");
    #endif

    _title      = Title;
    _size       = size;
    _MARGIN     = Margin;
    _TitleColor = TitleColor;
    _RealtimeRedraw = RealtimeRedraw;

    /*Ненавижу байтодрочерство*/

             /*DCBAYYYY*/
    _style = 0b00100000;
    if(Resize)
    {
        _style += WindowStyle::CanResize;
    }
    else
    {
        _style += WindowStyle::FixSize;
    }

    if(Gradient)
    {
        _style += WindowStyle::GradientDraw;
    }
    else
    {
        _style += WindowStyle::NormalDraw;
    }


    if (colors == Colors::DefaultColorTable) // Если небыла в аргументах таблица цветов
    {                                                                      // Используется системная
        _colors = OS::sys_color_table;
    }
    else
    {
        _colors = colors;
    }

    window::CreateWindow(DefaultWindowCoord, _size, _title, _colors.frame_area, _TitleColor, _style); // Отрисовать окно
}

Window::~Window()
{
}

void KolibriLib::window::Window::Redraw()
{
    StartRedraw();
    window::CreateWindow(DefaultWindowCoord, _size, _title, _colors.frame_area, _TitleColor, _style);
    graphic::DrawRectangleFill({0, (int)window::GetSkinHeight()}, GetWindowSize(), _colors.frame_area);

    for (int i = 0; i < _maxElement; i++)
    {
        auto it = _Elements.find(i);
        if (it != _Elements.end())
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
                break;
            case Element::Type::Frame:
                _Elements[i].frame->Render();
                break;
            case Element::Type::Menu:
                _Elements[i].menu->Render();
                break;
            default:
                _ksys_debug_puts("KolibriLib::window::Window::Render unknown type, break\n");
                break;
            }
        }
    }

    if (_Transparency != 0) // Прозрачность окна
    {
        point<unsigned> size = GetWindowSize();
        for (unsigned i = 0; i < size.y; i++)
        {
            for (unsigned j = 0; j < size.x; j++)
            {
                graphic::DrawPixel({(int)j, (int)i}, graphic::ReadPoint({j, i}) + ReadBackgroungImagePoint({j, i})); // Пока так, потом может быть станет лучше
            }
        }
    }

    EndRedraw();
}

void Window::SetWindowColors(const Colors::ColorsTable &colorTable)
{
    _colors = colorTable;
}

void Window::StartRedraw()
{
    _ksys_start_draw();
    _Redraw = true;
}

void Window::EndRedraw()
{
    if (_Redraw)
    {
        _ksys_end_draw();
        _Redraw = false;
    }
}

const UI::Coord &KolibriLib::window::Window::GetCoord() const
{
    window::GetWindowCoord();
}

void Window::ChangeWindow(UI::Coord coord, UI::Size size)
{
    _size = size;
    _ksys_change_window(coord.x, coord.y, size.x, size.y);
}

void Window::ChangeTilte(const std::string &newTitle)
{
    _ksys_set_window_title(newTitle.c_str());
}

UI::Size Window::GetWindowSize()
{
    return _size;
}
void Window::Render(UI::Coord coord)
{
    StartRedraw();
    window::CreateWindow(coord, _size, _title, _colors.frame_area, _TitleColor, _style);

    for (int i = 0; i < _maxElement; i++)
    {
        auto it = _Elements.find(i);
        if (it != _Elements.end())
        {
            if(it->second._type == Element::Type::Button)
            {
                it->second.btn->Render();
            }
        }
    }

    if(_Transparency != 0)  //Прозрачность окна
    {
        UI::Size size = GetWindowSize();
        for(int i = 0; i < size.y; i++)
        {
            for(int j = 0; j < size.x; j++)
            {
                graphic::DrawPixel({j, i}, graphic::ReadPoint({(unsigned)j, (unsigned)i}) + ReadBackgroungImagePoint({(unsigned)j, (unsigned)i})); // Пока так, потом может быть станет лучше
            }
        }
    }

    EndRedraw();
}

unsigned Window::GetMargin()
{
    return _MARGIN;
}

UI::Size Window::GetSize()
{
    return _size;
}


void Window::DeleteElement(int id)
{
    if(_Elements.count(i))
    {
        _Elements.erase(id);
        if(id == _maxElement)
        {
            
        }
    }

}

OS::Event Window::Handler()
{
    OS::Event event = OS::WaitEvent(8);

    switch (event)
    {
    case OS::Events::Redraw:

        Render();

        break;
    case OS::Events::Button:

        if (UI::buttons::GetPressedButton() == 1) // Если нажата кнопка X
        {
            return OS::Events::Exit;
        }

        for (int i = 0; i < _maxElement; i++) // Запуск обработчиков всех используемых элементов
        {
            auto it = _Elements.find(i);
            if (it != _Elements.end())
            {
                switch (it->second._type)
                {
                case Element::Type::Form:
                    it->second.form->ButtonHandler();
                case Element::CheckBox:
                    it->second.checkbox->Handler();
                case Element::Button:
                    it->second.btn->Handler();
                }
            }
        }

        break;
    case OS::Events::Key:

        if(activeForm != -1)
        {
            _Elements[activeForm].form->Handler(); // Обработчик активной на текущий момент формы
        }

        break;
    }
    if(_RealtimeRedraw)
    {
        UI::Coord Mouse = mouse::GetMousePositionInWindow();
        if (((Mouse.x > 0 && Mouse.y > 0) && Mouse.x < GetWindowSize().x && Mouse.y < GetSkinHeight()) && mouse::GetMouseButtons() == mouse::LeftButton)
        {
            while (mouse::GetMouseButtons() == mouse::LeftButton)
            {
                Render(mouse::GetMousePositionOnSreen() - Mouse);
                _ksys_thread_yield();
            }
        }
    }

    return event;
}

UI::buttons::ButtonID Window::GetPressedButton()
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (_Elements[i]._type == Element::Type::Button)
        {
            if (_Elements[i].btn->GetStatus())
            {
                return _Elements[i].btn->GetId();
            }
        }
    }
}
const std::string& Window::GetInputFromFrom(int form) const
{
    auto it = _Elements.find(form);
    if (it != _Elements.end())
    {
        return it->second.form->GetInput();
    }
}

void KolibriLib::window::Window::Unfocus() const
{
    _ksys_unfocus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
}

void KolibriLib::window::Window::Focus() const
{
    _ksys_focus_window(Thread::GetThreadSlot(Thread::GetThreadInfo(-1).pid));
}

template <class T>
int Window::AddElement(const T &element)
{
    Element a;
    
    a.SetElement(element);

    

    for (unsigned i = 0; i < _Elements.max_size(); i++) // Ищем свободный элемент
    {
        if (_Elements.count(i) == 0)
        {
            _Elements[i] = a;

            if(i > _maxElement)
            {
                _maxElement = i;
            }

            return i;
        }
    }

    return -1;
}

template <class T>
void KolibriLib::window::Window::SetElement(int i, const T &element)
{
    if (_Elements.count(i))
    {
        _Elements[i].SetElement(element);
        return;
    }
    _ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");
}

template <class T>
const T& KolibriLib::window::Window::GetElement(int i) const
{
    auto it = _Elements.find(i);
    if ( it != _Elements.end())
    {
        switch (it->second._type)
        {
        case Element::Type::TextLabel:
            return it->second.txt;
        case Element::Type::Button:
            return it->second.btn;
        case Element::Type::Image:
            return it->second.img;
        case Element::Type::Form:
            return it->second.form;
        case Element::Type::CheckBox:
            return it->second.checkbox;
        case Element::Type::Frame:
            return it->second.frame;
        case Element::Type::Menu:
            return it->second.menu;
        default:
            _ksys_debug_puts("KolibriLib::window::Window::GetElement: unknown type, break\n");
            break;
        }
    }
    _ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");
    
    return 0;
}
