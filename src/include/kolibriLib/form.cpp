#include "form.hpp"

using namespace KolibriLib;
using namespace UI;

Form::Form(const Coord &coord, const Size &size, const std::string &BackgroundText, const Colors::Color &FormColor, const Colors::Color &ButtonTextColor, const unsigned &Margin) : UIElement(coord, size, FormColor, Margin)
{
    #ifdef DEBUG == true
    _ksys_debug_puts("Form Constructor\n");
    #endif
    _e = kolibri_new_editor(X_Y(coord.x, coord.y), X_Y(size.x, size.y), , , &_ed_lock);
    ted_text_add(_e, (char*)BackgroundText.c_str(), BackgroundText.length(), 0);
}

void Form::init(Coord coord, Size size, std::string BackgroundText, Colors::Color FormColor, Colors::Color ButtonTextColor, unsigned Margin)
{
    
}

std::string Form::GetBackgroundText() const
{
    
}

Colors::Color Form::GetBackgroundColor() const
{
    
}

void KolibriLib::UI::Form::SetBackgroundText(const std::string &NewText)
{
    
}

void KolibriLib::UI::Form::SetBackgroundColor(const Colors::Color &NewColor)
{
    
}

Form::~Form()
{
}

void Form::Render()
{
    
}

std::string Form::GetInput() const
{
    
}

void Form::Handler()
{
    
}
bool Form::ButtonHandler()
{
    
}