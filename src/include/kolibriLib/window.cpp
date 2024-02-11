#include "window.hpp"

using namespace KolibriLib;
using namespace UI;
using namespace window;

unsigned Window::AddNewButton(UI::buttons::Button btn)
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (!_Elements[i].use)
        {
            switch (btn.GetType())
            {
            case UI::buttons::Button::Type::Image:
                _Elements[i].btn = btn;
                break;
            case UI::buttons::Button::Type::Text:
                _Elements[i].btn = btn;
                break;
            default:
                break;
            }
            _Elements[i]._type = Element::Type::Button;
            _Elements[i].use = true;
            return i;
        }
    }
    Element a;
    switch (btn.GetType())
    {
    case UI::buttons::Button::Type::Image:
        a.btn = btn;
        break;
    case UI::buttons::Button::Type::Text:
        a.btn = btn;
    default:
        break;
    }
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
            _Elements[i].txt = text;
            _Elements[i]._type = Element::Type::TextLabel;
            _Elements[i].use = true;

#if DEBUG == true
            _ksys_debug_puts("done\n");
#endif

            return i;
        }
    }

    Element a;

    a.use = true;

    a.txt = text;

    _Elements.push_back(a);
}

unsigned Window::AddNewForm(UI::Form form)
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (!_Elements[i].use)
        {
            _Elements[i].frm = form;
            _Elements[i]._type = Element::Type::Form;
            _Elements[i].use = true;
            return i;
        }
    }
    Element a;
    a.frm = form;
    a.use = true;
    a._type = Element::Type::Form;
    _Elements.push_back(a);
    return _Elements.size();
}

Window::Window(const std::string &Title, const UI::Size &size, const Colors::ColorsTable &colors, const Colors::Color &TitleColor, bool Resize, bool Gradient, unsigned Transparency, const unsigned &Margin)
{
    #if DEBUG == true
    _ksys_debug_puts("KolibriLib::window:::Window constructor\n");
    #endif

    _title      = Title;
    _size       = size;
    _MARGIN     = Margin;
    _TitleColor = TitleColor;

             /*DCBAYYYYRRRRRRRRGGGGGGGGBBBBBBBB*/
    _style = 0b00100000;
    if(Resize)
    {             /*DCBAYYYYRRRRRRRRGGGGGGGGBBBBBBBB*/
        _style += 0b00000011;
    }
    if(Gradient)
    {             /*DCBAYYYYRRRRRRRRGGGGGGGGBBBBBBBB*/
        _style += 0b10000000;
    }


    if (Colors::ComparisonColorsTables(colors, Colors::DefaultColorTable)) // Если небыла в аргументах таблица цветов
    {                                                                      // Используется системная
        _colors = OS::GetSystemColors();
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
void Window::Render()
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
            case Element::Type::Button:
                _Elements[i].btn.Render();
                break;
            case Element::Type::TextLabel:
                _Elements[i].txt.Render();
                break;
            case Element::Type::CheckBox:
                _Elements[i].ChckBx.Render();
                break;
            case Element::Type::Image:
                _Elements[i].img.Render();
                break;
            case Element::Type::Form:
                _Elements[i].frm.Render();
                break;
            case Element::Type::Frame:
                _Elements[i].frame.Render();
                break;
            default:
                _ksys_debug_puts("Error in KolibriLib::window::Window::Render(): unklown type\n");
                break;
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

unsigned KolibriLib::window::Window::CreateButton(UI::Coord coord, UI::Size size, std::string Text, unsigned margin, bool UseWindowColors, Colors::Color color, Colors::Color TextColor)
{
    if (UseWindowColors)
    {
        color = _colors.work_button;
        TextColor = _colors.work_button_text;
    }
    return AddNewButton(UI::buttons::Button(coord, size, margin, color));
}

unsigned Window::CreateText(UI::Coord coord, UI::Size size, std::string text, unsigned FontSize, bool UseWindowColors, Colors::Color color)
{
    #if DEBUG == true
    _ksys_debug_puts("CreateText:");
    #endif
    if (UseWindowColors)
    {
        color = _colors.work_text;
    }

    return AddNewTextLabel(UI::text::TextLabel(coord, size, text, FontSize, true, color, _MARGIN));
}

unsigned Window::CreateText(const UI::text::TextLabel &text)
{
    return AddNewTextLabel(UI::text::TextLabel(text));
}

void Window::DeleteElement(unsigned id)
{
    _Elements[id].use = false;
}

OS::Event Window::Handler()
{
    OS::Event event = OS::WaitEvent(10);

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

                    _Elements[i].frm.ButtonHandler();
                case Element::CheckBox:
                    _Elements[i].ChckBx.Handler();
                case Element::Button:
                    _Elements[i].btn.Handler();
                }
            }
        }

        break;
    case OS::Events::Key:

        _Elements[activeForm].frm.Handler(); // Обработчик активной на текущий момент формы

        break;
    }
    return event;
}

UI::buttons::ButtonID Window::GetPressedButton()
{
    for (int i = 0; i < _Elements.size(); i++)
    {
        if (_Elements[i]._type == Element::Type::Button)
        {
            if (_Elements[i].btn.GetStatus())
            {
                return _Elements[i].btn.GetId();
            }
        }
    }
}
std::string Window::GetInputFromFrom(unsigned form)
{
    if (_Elements[form]._type == Element::Type::Form)
    {
        return _Elements[form].frm.GetInput();
    }
}

UI::buttons::Button Window::GetButton(unsigned id)
{
    return _Elements[id].btn;
}

void Window::HandlerThread()
{
    while (true)
    {
        if (Handler() == OS::Events::Exit)
        {
            break;
        }
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

    switch (sizeof(T))
    {
    case sizeof(UI::text::TextLabel):
        a.txt = element;
        a._type = Element::Type::TextLabel;
        break;
    case sizeof(UI::buttons::Button):
        a.btn = element;
        a._type = Element::Type::Button;
        break;
    case sizeof(UI::Images::Image):
        a.img = element;
        a._type = Element::Type::Image;
        break;
    case sizeof(UI::Form):
        a.frm = element;
        a._type = Element::Type::Form;
        break;
    case sizeof(UI::CheckBox):
        a.ChckBx = element;
        a._type = Element::Type::CheckBox;
        break;
    case sizeof(UI::Frame):
        a.frmae = element;
        a._type = Element::Type::Form;
    case sizeof(UI::Menu):
        a.menu = element;
        a._type = Element::Type::Menu;
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
    case sizeof(UI::Frame):
        _Elements[i].frmae = element;
        _Elements[i]._type = Element::Type::Form;
    case sizeof(UI::Menu):
        _Elements[i].menu = element;
        _Elements[i]._type = Element::Type::Menu;
    default:
        _ksys_debug_puts("KolibriLib::window::Window::AddElement: unknown type, break\n");
        break;
    }
}
