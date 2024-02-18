#include "window.hpp"

using namespace KolibriLib;
using namespace UI;
using namespace window;

Window::Element::Element()
{
	use			= false;
	_type		= Type::None;
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

unsigned Window::AddNewButton(const UI::buttons::Button& btn)
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (!_Elements[i].use)
        {
            _Elements[i].SetElement(btn);
            _Elements[i]._type = Element::Type::Button;
            _Elements[i].use = true;
            return i;
        }
    }
    Element a;
    a.SetElement(btn);
    a._type = Element::Type::Button;
    a.use = true;
    _Elements.push_back(a);
    return _Elements.size();
}



unsigned Window::AddNewTextLabel(UI::text::TextLabel text)
{
    #if DEBUG == true
    _ksys_debug_puts("AddNewText:");
    #endif

    for (unsigned i = 0; i < _Elements.size(); i++)
    {
        #if DEBUG == true
        char *a = "find, try #";
        char *b = (char *)('0' + (char)i);
        strcat(b, ".\n");
        strcat(a, b);
        _ksys_debug_puts(a);
        #endif

        if (!_Elements[i].use)
        {
            _Elements[i].SetElement(text);
            _Elements[i]._type = Element::Type::TextLabel;
            _Elements[i].use = true;

            #if DEBUG == true
            _ksys_debug_puts("done\n");
            #endif

            return i;
        }
    }

    Element a;

    a._type = Element::Type::TextLabel;
    a.use = true;
    a.SetElement(text);

    _Elements.push_back(a);
}

unsigned Window::AddNewForm(UI::Form form)
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (!_Elements[i].use)
        {
            _Elements[i].SetElement(form);
            _Elements[i]._type = Element::Type::Form;
            _Elements[i].use = true;
            return i;
        }
    }
    Element a;
    a.SetElement(form);
    a.use = true;
    a._type = Element::Type::Form;
    _Elements.push_back(a);
    return _Elements.size();
}

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


    if (Colors::ComparisonColorsTables(colors, Colors::DefaultColorTable)) // Если небыла в аргументах таблица цветов
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

    for (int i = 0; i < _Elements.size(); i++)
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

    for (int i = 0; i < _Elements.size(); i++)
    {
        if (_Elements[i].use)
        {
            if(_Elements[i]._type == Element::Type::Button)
            {
                _Elements[i].btn->Render();
            }
        }
    }

    if(_Transparency != 0)  //Прозрачность окна
    {
        point<unsigned> size = GetWindowSize();
        for(unsigned i = 0; i < size.y; i++)
        {
            for(unsigned j = 0; j < size.x; j++)
            {
                graphic::DrawPixel({(int)j, (int)i}, graphic::ReadPoint({j, i}) + ReadBackgroungImagePoint({j,i})); //Пока так, потом может быть станет лучше
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


void Window::DeleteElement(unsigned id)
{
    _Elements[id].use = false;
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

        for (int i = 0; i < _Elements.size(); i++) // Запуск обработчиков всех используемых элементов
        {
            if (_Elements[i].use)
            {
                switch (_Elements[i]._type)
                {
                case Element::Type::Form:
                    _Elements[i].form->ButtonHandler();
                case Element::CheckBox:
                    _Elements[i].checkbox->Handler();
                case Element::Button:
                    _Elements[i].btn->Handler();
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
std::string Window::GetInputFromFrom(unsigned form)
{
    if (_Elements[form]._type == Element::Type::Form)
    {
        return _Elements[form].form->GetInput();
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
unsigned Window::AddElement(const T &element)
{
    Element a;
    
    a.SetElement(element);

    switch (sizeof(T))
    {
    case sizeof(UI::text::TextLabel):
        a._type = Element::Type::TextLabel;
        break;
    case sizeof(UI::buttons::Button):
        a._type = Element::Type::Button;
        break;
    case sizeof(UI::Images::Image):
        a._type = Element::Type::Image;
        break;
    case sizeof(UI::Form):
        a._type = Element::Type::Form;
        break;
    case sizeof(UI::CheckBox):
        a._type = Element::Type::CheckBox;
        break;
    case sizeof(UI::Frame):
        a._type = Element::Type::Form;
        break;
    case sizeof(UI::Menu):
        a._type = Element::Type::Menu;
        break;
    default:
        _ksys_debug_puts("KolibriLib::window::Window::AddElement: unknown type, break\n");
        break;
    }

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
void KolibriLib::window::Window::SetElement(unsigned i, const T &element)
{
    if (i >= _Elements.size())
    {
        _ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");
        return;
    }
    switch (sizeof(T))
    {
    case sizeof(UI::text::TextLabel):
        _Elements[i].txt = element;
        _Elements[i]._type = Element::Type::TextLabel;
        break;
    case sizeof(UI::buttons::Button):
        _Elements[i].btn = element;
        _Elements[i]._type = Element::Type::Button;
        break;
    case sizeof(UI::Images::Image):
        _Elements[i].img = element;
        _Elements[i]._type = Element::Type::Image;
        break;
    case sizeof(UI::Form):
        _Elements[i].frm = element;
        _Elements[i]._type = Element::Type::Form;
        break;
    case sizeof(UI::CheckBox):
        _Elements[i].ChckBx = element;
        _Elements[i]._type = Element::Type::CheckBox;
        break;
    case sizeof(UI::Menu):
        _Elements[i].menu = element;
        _Elements[i]._type = Element::Type::Menu;
        break;
    default:
        _ksys_debug_puts("KolibriLib::window::Window::AddElement: unknown type, break\n");
        break;
    }
}

template <class T>
T KolibriLib::window::Window::GetElement(unsigned i) const
{
    if(i >= _Elements.size())
    {
        _ksys_debug_puts("KolibriLib::window::Window::SetElement: i >= _Elements.size(), return\n");
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
        return _Elements[i].frm;
    case Element::Type::CheckBox:
        return _Elements[i].ChckBx;
    case Element::Type::Frame:
        return _Elements[i].frame;
    case Element::Type::Menu:
        return _Elements[i].menu;
    default:
        _ksys_debug_puts("KolibriLib::window::Window::GetElement: unknown type, break\n");
        break;
    }
    return 0;
}
