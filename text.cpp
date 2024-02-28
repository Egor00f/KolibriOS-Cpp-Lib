#include <kolibriLib/UI/text.hpp>
#include "text.hpp"

using namespace KolibriLib;
using namespace UI;
using namespace text;

text::TextLabel::TextLabel(const Coord &coord, const Size &size, const std::string &text, const unsigned &FontSize, bool TextScale, const Colors::Color &TextColor, const unsigned &Margin) : UIElement(coord, size, TextColor, Margin)
{
#if DEBUG == true
	_ksys_debug_puts("TextLabel Constructor \n");
#endif;
	Add(text);
	_TextScale = TextScale;
}

text::TextLabel::~TextLabel()
{
}

void text::TextLabel::Render() const
{
	unsigned* FontSize = new unsigned;
	*FontSize = 0;
	if (_TextScale) // Если текст нужно подстраивать размер, то
	{			   // Постраиваем
		*FontSize = _size.x / length();
	}
	if(!_Aligned)
	{
		for(int i = 0; i < _data.size(); i++)
		{
			_data[i].SetSize({*FontSize, _data[i].GetSize().y});
		}
		_Aligned = true;
	}
	Print(_coord);
	
}

void text::TextLabel::SetScale(bool scale)
{
	_TextScale = scale;
}


text::TextLabel &KolibriLib::UI::text::TextLabel::operator=(const TextLabel &a)
{
	_coord	  = a._coord;
	_size	   = a._size;
	_MainColor  = a._MainColor;
	_Margin	 = a._Margin;
	_TextScale  = a._TextScale;
	return *this;
}

bool KolibriLib::UI::text::TextLabel::operator==(const TextLabel &a) const
{
	return (_coord == a._coord) && 
			(_size == a._size) && 
			(_MainColor == a._MainColor) && 
			(_Margin == a._Margin) && 
			(_TextScale == a._TextScale);
}

bool KolibriLib::UI::text::TextLabel::operator!=(const TextLabel &a) const
{
	return (_coord == a._coord) ||
		   (_size == a._size) ||
		   (_MainColor == a._MainColor) ||
		   (_Margin == a._Margin) ||
		   (_TextScale == a._TextScale);
	;
}

KolibriLib::UI::text::Char::Char(char c, const UI::Size &size, const unsigned flags, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
{
	_c			   = new char(c);
	_size			= new UI::Size(size);
	_TextColor	   = new Colors::Color(TextColor);
	_BackgroundColor = new Colors::Color(BackgroundColor);
	_flags		   = new unsigned(flags);
	_type			= Type::Text;
}

KolibriLib::UI::text::Char::Char(const Images::img &img, const UI::Size& size)
{
	_img = new Images::img(img);
	_size = size;
	_type = Type::Image;
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
	*_flags = flags;
}

void KolibriLib::UI::text::Char::SetTextColor(const Colors::Color &NewColor)
{
	assert(_type == Type::Text);
	*_TextColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetBackgroundColor(const Colors::Color & NewColor)
{
	assert(_type == Type::Text);
	*_BackgroundColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetSize(const UI::Size &size) const
{
	assert(_type == Type::Text);
	*_size = size;
}

char KolibriLib::UI::text::Char::GetChar() const
{
	assert(_type == Type::Text);
  return *_c;
}

const UI::Size &KolibriLib::UI::text::Char::GetSize() const
{
	assert(_type == Type::Text);
	return *_size;
}

unsigned KolibriLib::UI::text::Char::GetFlags() const
{
	assert(_type == Type::Text);
  return *_flags;
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
		DrawText(std::string(_c), coord, *_size, *_flags, 4, *_TextColor, *_BackgroundColor);
		break;
	default:
		break;
	}
}

KolibriLib::UI::text::Text::Text()
{

}

KolibriLib::UI::text::Text::~Text()
{

}

void KolibriLib::UI::text::Text::Add(const Char &c)
{
	_data.push_back(c);
}

void KolibriLib::UI::text::Text::Add(const std::string &txt)
{
	_data.push_back(Char(txt[0]));	//На случай если вектор пустой
	for(int i = 1; i < txt.length(); i++)
	{
		_data.push_back(Char(txt[i]);
	}
}

void KolibriLib::UI::text::Text::Add(const Images::img &img)
{
	_data.push_back(Char(img));
}
void KolibriLib::UI::text::Text::insert(const Char &c, int i)
{
	_data.insert(_data.begin() + i, c);
}

void KolibriLib::UI::text::Text::insert(const std::string &txt, int i)
{
	for(int j = txt.length(); j > 0; j++)
	{
		_data.insert(_data.begin() + i, Char(txt[j], {9, 16}));
	}
}

void KolibriLib::UI::text::Text::insert(const Images::img &img, int i)
{
	_data.insert(_data.begin() + i, Char(img));
}

void KolibriLib::UI::text::Text::Delete(int i)
{
	_data.erase(_data.begin() + i);
}

void KolibriLib::UI::text::Text::Print(const UI::Coord &coord) const
{
	int buff = 0;
	for(int i = 0; i < _data.size(); i++)
	{
		_data[i].Print({coord.x + buff, coord.y});
		buff += _data[i].GetSize().x;
	}

}

void KolibriLib::UI::text::Text::SetSize(UI::Size FontSize)
{
	for(int i = 0; i < _data.size(); i++)
	{
		_data[i].SetSize(FontSize);
	}
}

bool KolibriLib::UI::text::Text::operator==(const Text &txt) const
{
  return _data == txt._data;
}

std::size_t KolibriLib::UI::text::Text::length() const
{
  return _data.size();
}

Text &KolibriLib::UI::text::Text::operator=(const Text &txt)
{
  _data = txt._data;
	return *this;
}

void KolibriLib::UI::text::DrawText(const std::string & text, const Coord & coord, const Size & size, unsigned flags, unsigned margin, const Colors::Color & colorText, const Colors::Color &BackgroundColor)
{
	const unsigned w = ((margin * 2) + size.x);
	const unsigned h = ((margin * 2) + (size.y * text.length()));

	rgb_t *canvas = new rgb_t[w * h];
	
	for(int i = 0; i < w*h; i++)
	{
	  canvas[i].val = BackgroundColor.val;
	}

	drawText(canvas, coord.x, coord.y, text.c_str(), text.length(), colorText.val, flags);
	_ksys_draw_bitmap(canvas, coord.x, coord.y, w, h);
	
	delete[] canvas;
}