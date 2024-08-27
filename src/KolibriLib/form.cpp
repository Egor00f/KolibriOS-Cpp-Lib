#include <kolibriLib/UI/form.hpp>

using namespace KolibriLib;
using namespace UI;

Form::Form(const UDim &coord, const UDim &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin) 
	:	UIElement	(coord, size, FormColor, Margin)
{
	_butt.SetCoord	(coord);
	_butt.SetSize	(size);
	_butt.SetTextColor	(ButtonTextColor);
	_butt.Add	(BackgroundText);

}

std::string Form::GetBackgroundText() const
{
	return _butt.GetText();
}

Colors::Color Form::GetBackgroundColor() const
{
	return _butt.GetColor();
}

void Form::SetBackgroundColor(const Colors::Color &NewColor)
{
	_butt.SetColor(NewColor);
}

void Form::Render() const
{
	graphic::DrawRectangleLines(GetAbsoluteCoord(), GetAbsoluteCoord() + GetAbsoluteSize());
	_butt.Render();
}

std::string Form::GetInput() const
{
	return _inputText;
}

void Form::OnKeyEvent()
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

void Form::OnButtonEvent(buttons::ButtonID PressedButtonID)
{
	_butt.OnButtonEvent(PressedButtonID);
}

void KolibriLib::UI::Form::SetBackgroundText(const std::string &NewText)
{
	_butt.SetText(NewText);
}