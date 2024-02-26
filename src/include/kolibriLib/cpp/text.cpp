#include <kolibriLib/UI/text.hpp>
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



KolibriLib::UI::text::Char::Char(char c, const UI::Size &size, const unsigned flags, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
{
    _c = new char(c);
    _size = new UI::Size(size);
    _TextColor = new Colors::Color(TextColor);
    _BackgroundColor = new Colors::Color(BackgroundColor);
    _flags = new unsigned(flags);
    _type = Type::Text;
}

KolibriLib::UI::text::Char::~Char()
{
    Char::Free();
}

short KolibriLib::UI::text::Char::GetType() const
{
	return _type;
}

void KolibriLib::UI::text::Char::Set(const char c, const UI::Size &size, const unsigned flags = 0, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
{
    Char::Free();   //Пофиг какой раньше тип был, просто тупо сносим и делаем всё заново
    _size = new UI::Size(size);
    _TextColor = new Colors::Color(TextColor);
    _BackgroundColor = new Colors::Color(BackgroundColor);
    _flags = new unsigned(flags);
    _c = new char(c);
    _type = Type::Text;
}

void KolibriLib::UI::text::Char::Set(const Images::Image &img)
{
    Char::Free();
    _img = new Images::Image(img);
    _type = Type::Image;
}

void KolibriLib::UI::text::Char::SetFlags(unsigned flags)
{
    assert(_type == Type::Text);
    delete _flags;
    _flags = new unsigned(flags);
}

void KolibriLib::UI::text::Char::SetTextColor(const Colors::Color &NewColor)
{
    assert(_type == Type::Text);
    _TextColor->val = NewColor.val;
}

void KolibriLib::UI::text::Char::SetBackgroundColor(const Colors::Color & NewColor)
{
    assert(_type == Type::Text);
    _BackgroundColor->val = NewColor.val;
}

char KolibriLib::UI::text::Char::GetChar() const
{
    assert(_type == Type::Text);
	return *_c;
}

void KolibriLib::UI::text::Char::Free()
{
    switch (_type)
    {
    case Type::Image:
        delete _img;
        break;
    case Type::Text:
        delete _c;
        delete _TextColor;
        delete _BackgroundColor;
        delete _flags;
        delete _size;
        break;
    default:
        break;
    }
}

void KolibriLib::UI::text::Char::Print(const UI::Coord &coord) const
{
    switch (_type)
    {
    case Type::Image:
        _img->Render(coord, {_size->x, _size->y});
        break;
    case Type::Text:
        DrawText(_c, coord, *_size, _flags, 4, _TextColor, _BackgroundColor);
        break;
    default:
        break;
    }
}

void KolibriLib::UI::text::Text::Print(const UI::Coord &coord, unsigned FontSize) const
{
    unsigned i = 0;
    while(i < _data.size())
    {
        for (std::size_t j = i; j < _data.size() - 1; j++)
        {
            if (_data[j] != _data[j + 1])
            {
                i += j;
                break;
            }
        }
    }

}

void KolibriLib::UI::text::DrawText(const std::string & text, const Coord & coord, const Size & size, unsigned flags, unsigned margin, const Colors::Color & colorText, const Colors::Color BackgroundColor)
{
    unsigned w = ((margin * 2) + size.x);
    unsigned h = ((margin * 2) + (size.y * text.length()));

    rgb_t *canvas = new rgb_t[w * h];

    drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, flags);
    _ksys_draw_bitmap(canvas, coord.x, coord.y, w, h);
}
