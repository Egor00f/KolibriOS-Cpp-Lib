#include <kolibriLib/window/window.hpp>

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
        case Element::Type::Frame:
            n.second.frame->Render();
            break;
        case Element::Type::Menu:
            n.second.menu->Render();
            break;
        default:
            _ksys_debug_puts("KolibriLib::window::Window::Render unknown type, break\n");
            break;
        }
    }

    if (_Transparency != 0) // Прозрачность окна
    {
        UI::Size size = GetWindowSize();
        for (int i = 0; i < size.y; i++)
        {
            for (int j = 0; j < size.x; j++)
            {
                graphic::DrawPixel({j, i}, graphic::ReadPoint({j, i}) + Background::ReadPoint({j, i})); // Пока так, потом может быть станет лучше
            }
        }
    }

    EndRedraw();
}

void Window::SetWindowColors(const Colors::ColorsTable &colorTable)
{
    _colors = colorTable;
}

void Window::StartRedraw() const
{
    _ksys_start_draw();
    _Redraw = true;
}

void Window::EndRedraw() const
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

void Window::ChangeWindow(const UI::Coord& coord, const UI::Size& size)
{
    _size = size;
    _ksys_change_window(coord.x, coord.y, size.x, size.y);
}

void Window::ChangeTilte(const std::string &newTitle)
{
    _ksys_set_window_title(newTitle.c_str());
}

const UI::Size& Window::GetWindowSize() const
{
    return _size;
}

void Window::Render(const UI::Coord& coord)
{
    StartRedraw();
    window::CreateWindow(coord, _size, _title, _colors.frame_area, _TitleColor, _style);

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
        case Element::Type::Frame:
            n.second.frame->Render();
            break;
        default:
            break;
        }
    }

    if(_Transparency != 0)  //Прозрачность окна
    {
        UI::Size size = GetWindowSize();
        for(int i = 0; i < size.y; i++)
        {
            for(int j = 0; j < size.x; j++)
            {
                graphic::DrawPixel({j, i}, graphic::ReadPoint({j, i}) + Background::ReadPoint({j, i})); // Пока так, потом может быть станет лучше
            }
        }
    }

    EndRedraw();
}

unsigned Window::GetMargin() const
{
    return _MARGIN;
}

const UI::Size& Window::GetSize() const
{
    return _size;
}


void Window::DeleteElement(int id)
{
    if(_Elements.count(id))
    {
        if(activeForm == id)
        {
            activeForm = -1;
        }
        _Elements.erase(id);
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

        for (const std::pair<int, Element> &n : _Elements) // Запуск обработчиков всех используемых элементов
        {
            switch (n.second._type)
            {
            case Element::Type::Form:
                n.second.form->ButtonHandler();
            case Element::CheckBox:
                n.second.checkbox->Handler();
            case Element::Button:
                n.second.btn->Handler();
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
    for (const std::pair<int, Element> &n : _Elements)
    {
        if (n.second._type == Element::Type::Button)
        {
            if (n.second.btn->GetStatus())
            {
                return n.second.btn->GetId();
            }
        }
    }
}
const std::string& Window::GetInputFromFrom(int form) const
{
    auto it = _Elements.find(form);
    if (it->second._type == Window::Element::Type::Form)
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

    auto it = _Elements.emplace(a);
    return it.first;


    //return -1;
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
