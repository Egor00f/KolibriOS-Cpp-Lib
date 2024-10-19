#include <kolibriLib/UI/BaseEditor.hpp>

using namespace KolibriLib;
using namespace UI;

BaseEditor::BaseEditor(const UDim &coord, const UDim &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin)
	: buttons::TextButton(coord, size, Margin, FormColor)
{
	logger << microlog::LogLevel::Debug << "BaseEditor constructor" << std::endl;

	SetText(BackgroundText);
}

bool KolibriLib::UI::BaseEditor::OnKeyEvent()
{
	logger << microlog::LogLevel::Debug <<"Redner BaseEditor" << std::endl;

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
	logger << microlog::LogLevel::Debug <<"BaseEditor ButtonEvent" << std::endl;

	bool ret = buttons::TextButton::OnButtonEvent(PressedButtonID);

	Active = GetStatus();

	return ret;
}