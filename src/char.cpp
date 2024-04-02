#include <kolibriLib/UI/text/char.hpp>

using namespace KolibriLib;
using namespace UI;
using namespace text;

KolibriLib::UI::text::Char::Char(const Images::img &img, const KolibriLib::UI::text::Fonts::Font &font)
	: _img(new Images::img(img)), _font(font), _type(Type::Image)
{
	
}

KolibriLib::UI::text::Char::Char(const char &c, const Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
	: _c(new char(c)), _font(font), _TextColor(new Colors::Color(TextColor)), _BackgroundColor(new Colors::Color(BackgroundColor)), _type(Type::Text)
{
	
}

KolibriLib::UI::text::Char::Char(const Char &copy) : _font(copy._font), _type(copy._type)
{
	switch (copy._type)
	{
	case Type::Text:
		_c = new char;
		std::memcpy(_c, copy._c, 1);

		_TextColor = new Colors::Color(copy._TextColor->val);
		_BackgroundColor = new Colors::Color(copy._BackgroundColor->val);

		break;
	case Type::Image:
		_img = new Images::img(copy._img->GetColorsMap(), copy._img->GetSize());

		break;
	default:
		break;
	}
}

KolibriLib::UI::text::Char::~Char()
{
	Char::Free();
}

uint8_t KolibriLib::UI::text::Char::GetType() const
{
	return _type;
}

void KolibriLib::UI::text::Char::Set(const char c, const Fonts::Font &font, const Colors::Color &TextColor, const Colors::Color &BackgroundColor)
{
	Char::Free(); // Пофиг какой раньше тип был, просто тупо сносим и делаем всё заново
	_font = font; // да это дольше, но проще
	_TextColor = new Colors::Color(TextColor);
	_BackgroundColor = new Colors::Color(BackgroundColor);
	_c = new char(c);
	_type = Type::Text;
}

void KolibriLib::UI::text::Char::Set(const Images::Image &img, const KolibriLib::UI::text::Fonts::Font &size)
{
	Char::Free();
	_img = new Images::Image(img);
	_font = size;
	_type = Type::Image;
}

void KolibriLib::UI::text::Char::SetFlags(unsigned flags)
{
	assert(_type == Type::Text);
	_font._Flags = flags;
}

void KolibriLib::UI::text::Char::SetTextColor(const Colors::Color &NewColor)
{
	assert(_type == Type::Text);
	*_TextColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetBackgroundColor(const Colors::Color &NewColor)
{
	assert(_type == Type::Text);
	*_BackgroundColor = NewColor.val;
}

void KolibriLib::UI::text::Char::SetFont(const KolibriLib::UI::text::Fonts::Font &newFont) const
{
	assert(_type == Type::Text);
	_font = newFont;
}

char KolibriLib::UI::text::Char::GetChar() const
{
	assert(_type == Type::Text);
	return *_c;
}

const Images::img KolibriLib::UI::text::Char::GetImg() const
{
	assert(_type == Type::Image);
	return *_img;
}

const Fonts::Font KolibriLib::UI::text::Char::GetFont() const
{
	return _font;
}

unsigned KolibriLib::UI::text::Char::GetFlags() const
{
	assert(_type == Type::Text);
	return _font._Flags;
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
		break;
	}
}

void KolibriLib::UI::text::Char::Print(const Coord &coord) const
{
	#ifdef DEBUG
	_ksys_debug_puts("Print Char:\n");
	#endif

	switch (_type)
	{
	case Type::Image:

		#ifdef DEBUG
		_ksys_debug_puts("Char is img");
		#endif

		_img->Draw(coord, _font.size);
		break;
	case Type::Text:

		#ifdef DEBUG
		_ksys_debug_puts("Char is text");
		#endif

		char *buff = new char[2];
		buff[0] = *_c;
		buff[1] = '\0';
		DrawText(std::string(buff), coord, _font, OS::GetSystemColors().work_text, *_TextColor, *_BackgroundColor);
		delete buff;
		break;
	}
}

KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(char c)
{
	*_c = c;
	if (_type != Char::Type::Text)
	{
		Free();
		_font = Fonts::DefaultFont;
		_TextColor = new Colors::Color(OS::GetSystemColors().work_text);
		_BackgroundColor = new Colors::Color(OS::GetSystemColors().work_area);
		_type = Type::Text;
	}
}

Char &Char::operator=(const Images::img &img)
{
	if (_type == Char::Type::Image)
	{
		*_img = img;
	}
	else
	{
		Free();
		_img = new Images::img(img);
		_type = Char::Type::Image;
	}
}

KolibriLib::UI::text::Char &KolibriLib::UI::text::Char::operator=(const KolibriLib::UI::text::Char &c)
{
	Free();
	_font = c._font;

	switch (c._type)
	{
	case Char::Type::Text:
		_c = c._c;
		_TextColor = new Colors::Color(c._TextColor->val);
		_BackgroundColor = new Colors::Color(c._BackgroundColor->val);
		_type = Type::Text;
		break;
	case Char::Type::Image:

		_img = new Images::img(*c._img);
		_type = Type::Image;

		break;
	default:
		break;
	}
}

bool Char::operator==(const Char &img) const
{
	return (_type == img._type) &&
		   (_font == img._font);
}

bool KolibriLib::UI::text::Char::operator==(const Images::img &img) const
{
	if(_type != Type::Image)
	{
		return false;
	}
	else
	{
		return _img->GetSize() == img.GetSize();
	}
}