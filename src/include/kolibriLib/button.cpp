#include "button.hpp"

unsigned KolibriLib::UI::buttons::GetFreeButtonId()
{
    for (unsigned i = 0; i < ButtonsIdList.size(); i++) // Проходим по всему массиву
    {                                                   // Если встречается свободный элемент,
        if (!ButtonsIdList[i].use)                      // То используем его
        {                                               // Иначе создаём новый и использем тоже новый
            ButtonsIdList[i].use = true;
            return i;
        }
    }
    ButtonsIdData a;
    a.use = true;
    ButtonsIdList.push_back(a);
    return ButtonsIdList.size() - 1; //-1 потому что обращение к элементам массива идёт с 0
}

void KolibriLib::UI::buttons::FreeButtonId(unsigned id)
{
    ButtonsIdList[id].use = false; // Этот элемент теперь не используется
}

KolibriLib::UI::buttons::ButtonID KolibriLib::UI::buttons::GetButtonId(unsigned id)
{
    return StartButtonId + id;
}

void KolibriLib::UI::buttons::CutList()
{
    unsigned a = ButtonsIdList.size();
    for (unsigned i = a; i < 0; i++)
    {
        if (ButtonsIdList[i].use)
        {
            a = i;
        }
        else
        {
            break;
        }
    }
    ButtonsIdList.erase(ButtonsIdList.begin() + a, ButtonsIdList.end());
}

KolibriLib::UI::buttons::ButtonID KolibriLib::UI::buttons::autoDefineButton(const Coord &coords, const Size &size, const Color::Color &color)
{
    unsigned id = GetButtonId(GetFreeButtonId()); // Автоматически получаем id для кнопки
    _ksys_define_button(coords.x, coords.y, size.x, size.y, id, color);
    return id;
}

void KolibriLib::UI::buttons::DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Color::Color color)
{
    _ksys_define_button(coord.x, coord.y, size.x, size.y, id, color);
}

void KolibriLib::UI::buttons::DeleteButton(unsigned id)
{
    _ksys_delete_button(id);
    FreeButtonId(id); // Кнопка удалена, теперь этот id не использется
}

KolibriLib::UI::buttons::ButtonID KolibriLib::UI::buttons::GetPressedButton()
{
    return _ksys_get_button();
}

KolibriLib::UI::buttons::Button::Button(const Coord &coord, const Size &size, unsigned Margin, Color::Color ButtonColor) : UIElement(coord, size, ButtonColor, Margin)
{
    _id = GetButtonId(GetFreeButtonId());
    _img.SetCoord(coord);
    _img.SetSize(size);
    _text.SetCoord(coord);
    _text.SetSize(size);
}

void KolibriLib::UI::buttons::Button::Deactivate()
{
    if (_active)
    {
        DeleteButton(_id);
        _active = false;
    }
}

void KolibriLib::UI::buttons::Button::Activate()
{
    if (!_active)
    {
        _id = GetButtonId(GetFreeButtonId());
        _active = true;
    }
}

unsigned KolibriLib::UI::buttons::Button::GetType()
{
    return _type;
}

std::string KolibriLib::UI::buttons::Button::GetTextLabel()
{
    if (_type == Type::Text)
    {
        return _text.GetText();
    }
}

KolibriLib::UI::Images::image KolibriLib::UI::buttons::Button::GetImage()
{
    return _img;
}

void KolibriLib::UI::buttons::Button::SetText(std::string NewText)
{
    if (_type == Type::Text)
    {
        return _text.SetText(NewText);
    }
}

KolibriLib::UI::buttons::Button::~Button()
{
    DeleteButton(_id);
}

bool KolibriLib::UI::buttons::Button::Handler()
{
    if (GetPressedButton() == _id)
    {
        _status = true;
    }
    else
    {
        _status = false;
    }
    return _status;
}

bool KolibriLib::UI::buttons::Button::GetStatus()
{
    return _status;
}

void KolibriLib::UI::buttons::Button::init(const Coord &coord, const Size &size, const std::string &text, const unsigned &Margin, const Color::Color &ButtonColor)
{
    _coord = coord;
    _size = size;
    _Margin = Margin;

    _text.SetText(text);
    _type = Type::Text;

    _text.SetCoord(coord);
    _text.SetSize(size);
    _text.SetScale(true);

    _MainColor = ButtonColor;

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void KolibriLib::UI::buttons::Button::init(const Coord &coord, const Size &size, const Images::image &image, const unsigned &Margin, const Color::Color &ButtonColor)
{
    _coord = coord;
    _size = size;
    _Margin = Margin;

    _img = image;
    _type = Type::Image;
    _img.SetCoord(coord);
    _img.SetSize(size);

    _MainColor = ButtonColor;

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void KolibriLib::UI::buttons::Button::init(const Coord &coord, const Size &size, std::string Path)
{
    _coord = coord;
    _size = size;

    _img.LoadImage(Path);
    _type = Type::Image;
    _img.SetCoord(coord);
    _img.SetSize(size);

    if (!_active) // Если кнопка была неактивна, то нужно её активировать
    {
        Activate();
    }
}

void KolibriLib::UI::buttons::Button::Render()
{
    if (_active)
    {
        DefineButton(_coord, _size, _id, _MainColor);

        switch (_type)
        {
        case Type::Image:
            _img.Render();
            break;
        case Type::Text:
            _text.Render();
            break;
        default:
            break;
        }
    }
}

KolibriLib::UI::buttons::ButtonID KolibriLib::UI::buttons::Button::GetId()
{
    return _id;
}