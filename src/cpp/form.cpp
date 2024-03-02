#include <kolibriLib/UI/form.hpp>

using namespace KolibriLib;
using namespace UI;

Form::Form(const Coord &coord, const Size &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin) : UIElement(coord, size, FormColor, Margin)
{
#ifdef DEBUG == true
    _ksys_debug_puts("Form Constructor\n");
#endif
    _butt.SetCoord(coord);
    _butt.SetSize(size);
    _butt.SetTextColor(ButtonTextColor);
    _butt.SetBackgroundColor(FormColor);
    _butt.Add(BackgroundText);
}

const std::string& Form::GetBackgroundText() const
{
    return _butt.GetText();
}

const Colors::Color& Form::GetBackgroundColor() const
{
    return _butt.GetColor();
}

Form::~Form()
{
}

void Form::Render() const
{
    graphic::DrawRectangleLines(_coord, {_coord.x + (int)_size.x, _coord.y + (int)_size.y}, _MainColor);

    _butt.Render();
}

const std::string& Form::GetInput() const
{
    return _inputText;
}

void Form::Handler()
{
    char input = keyboard::CheckKeyboard();
    if (input > 33 && input != 127) // Если введённый символ не является спецсимволом, и это не Delete
    {
        _inputText.push_back(input);
    }
    if (input == 127) // input = Delete
    {
        _inputText.erase(_inputText.end() - 1);
    }
}
bool Form::ButtonHandler()
{
    return _butt.Handler();
}