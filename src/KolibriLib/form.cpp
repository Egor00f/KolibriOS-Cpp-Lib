#include <kolibriLib/UI/form.hpp>

using namespace KolibriLib;
using namespace UI;

Form::Form(const UDim &coord, const UDim &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin) 
	: UIElement(coord, size, FormColor, Margin)
{
	_butt.get()->SetCoord(coord);
	_butt.get()->SetSize(size);
	_butt.get()->SetTextColor(ButtonTextColor);
	_butt.get()->Add(BackgroundText);

}

std::string Form::GetBackgroundText() const
{
	return _butt.get()->GetText();
}

Colors::Color Form::GetBackgroundColor() const
{
	return _butt.get()->GetColor();
}

void Form::SetBackgroundColor(const Colors::Color &NewColor)
{
	_butt.get()->SetColor(NewColor);
}

void Form::Render() const
{
	graphic::DrawRectangleLines(GetAbsoluteCoord(), GetAbsoluteCoord() + GetAbsoluteSize());
	_butt.get()->Render();
}

std::string Form::GetInput() const
{
	return _inputText;
}

int Form::Handler()
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
	return 0;
}

bool Form::ButtonHandler()
{
	return _butt.get()->Handler();
}

void KolibriLib::UI::Form::SetBackgroundText(const std::string &NewText)
{
	_butt.get()->SetText(NewText);
}