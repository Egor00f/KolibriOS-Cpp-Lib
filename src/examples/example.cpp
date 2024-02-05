#include "KolibriLib.hpp"

using namespace KolibriLib;

window::Window Window("Example");

bool Exit = false;

void WindowThread()
{
    while(true)
    {
        OS::Event event = Window.Handler();

        if(event == OS::Events::Exit)
        {
            Exit = true;
            Window.~Window();
        }
    }
}

int main()
{
    Thread::CreateThread((void(*)) WindowThread, 4096);

    Window.AddElement(UI::text::TextLabel({0,0}, Window.GetSize(), "Example text"));

    while (true)
    {
        if(Exit)
        {
            break;
        }
    }
    return 0;
}