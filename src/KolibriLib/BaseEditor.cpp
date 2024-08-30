#include <kolibriLib/UI/BaseEditor.hpp>

using namespace KolibriLib;
using namespace UI;

BaseEditor::BaseEditor(const UDim &coord, const UDim &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin)
	: buttons::TextButton(coord, size, Margin, FormColor)
{
	SetText(BackgroundText);
	textBuffStatus = false;
}

void KolibriLib::UI::BaseEditor::OnKeyEvent()
{
	buttons::TextButton::Render();

	if(Active && Visible)
	{
		char input = keyboard::CheckKeyboard();

		if(textBuffStatus)
		{
			SetText(GetText() + input);
		}
		else
		{
			textBuff += input;
		}
	}
}

void KolibriLib::UI::BaseEditor::OnMouseEvent()
{
	Active = Hover();
}

std::string KolibriLib::UI::BaseEditor::GetInput() const
{
	if(textBuffStatus)
	{
		return GetText();
	}
	else
	{
		return textBuff;
	}
}

void KolibriLib::UI::BaseEditor::OnButtonEvent(buttons::ButtonID PressedButtonID)
{
	buttons::TextButton::OnButtonEvent(PressedButtonID);

	Active = GetStatus();
}