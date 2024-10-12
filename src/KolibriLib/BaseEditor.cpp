#include <kolibriLib/UI/BaseEditor.hpp>

using namespace KolibriLib;
using namespace UI;

BaseEditor::BaseEditor(const UDim &coord, const UDim &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin)
	: buttons::TextButton(coord, size, Margin, FormColor)
{
	PrintDebug("BaseEditor constructor\n");

	SetText(BackgroundText);
}

bool KolibriLib::UI::BaseEditor::OnKeyEvent()
{
	PrintDebug("Redner BaseEditor\n");

	if(Active && Visible)
	{
		char input = keyboard::CheckKeyboard();

		SetText(GetText() + input);
	}

	buttons::TextButton::Render();
}

std::string KolibriLib::UI::BaseEditor::GetInput() const
{
	return GetText();
}

bool KolibriLib::UI::BaseEditor::OnButtonEvent(buttons::ButtonID PressedButtonID)
{
	PrintDebug("BaseEditor ButtonEvent\n");

	bool ret = buttons::TextButton::OnButtonEvent(PressedButtonID);

	Active = GetStatus();

	return ret;
}