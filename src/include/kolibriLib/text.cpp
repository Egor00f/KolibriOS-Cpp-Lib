#include "text.hpp"

using namespace KolibriLib;
using namespace UI;

text::TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) : UIElement(coord, size, TextColor, Margin)
{
#if DEBUG == true
    _ksys_debug_puts("TextLabel Constructor \n");
#endif
    _text = text;
    _FontSize = FontSize;
    _TextScale = TextScale;
}

text::TextLabel::~TextLabel()
{
}

void text::TextLabel::Render() const
{
    if (_TextScale) // Если текст нужно подстраивать размер, то
    {               // Постраиваем
        _FontSize = _size.x / _text.length();
    }

    unsigned a = _Margin;

    if ((_text.length() * _FontSize) > _size.x) // Центрирование текста
    {
        a = (_size.x / 2) - (_text.length() * _FontSize);
    }

    SetTextSize(_FontSize);
    DrawText(_text, {_coord.x + (int)a, _coord.y + ((int)_size.y / 2)}, _FontSize, _MainColor);
}

const std::string& text::TextLabel::GetText() const
{
    return _text;
}
unsigned text::TextLabel::GetFontSize() const
{
    return _FontSize;
}

void text::TextLabel::SetText(const std::string &NewText)
{
    _text = NewText;
}
void text::TextLabel::SetFontSize(const unsigned &NewTextSize)
{
    _FontSize = NewTextSize;
}

void text::TextLabel::SetScale(bool scale)
{
    _TextScale = scale;
}

void text::TextLabel::init(Coord coord, Size size, std::string text, unsigned FontSize, Colors::Color TextColor)
{
    SetCoord(coord);
    SetSize(size);
    SetText(text);
    SetColor(TextColor);
    SetFontSize(FontSize);
}

text::TextLabel &KolibriLib::UI::text::TextLabel::operator=(const TextLabel &a)
{
    _coord      = a._coord;
    _size       = a._size;
    _MainColor  = a._MainColor;
    _Margin     = a._Margin;
    _text       = a._text;
    _FontSize   = a._FontSize;
    _TextScale  = a._TextScale;
    return *this;
}

bool KolibriLib::UI::text::TextLabel::operator==(const TextLabel &a) const
{
    return (_coord == a._coord) && (_size == a._size) && (_MainColor == a._MainColor) && (_Margin == a._Margin) && (_text == a._text) && (_FontSize == a._FontSize) && (_TextScale == a._TextScale);
}
void KolibriLib::UI::text::Text::Render(UI::Coord coord, unsigned FontSize)
{
    
}
