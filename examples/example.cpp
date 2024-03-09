#include <KolibriLib.hpp>

using namespace KolibriLib;




void WindowThread()
{
    bool Exit = false;

    while(!Exit)
    {
        OS::Event event = Window.Handler();

        if(event == OS::Events::Exit)
            Exit = true;
    }
    Window.~Window();
}

int main()
{
    init();
    window::Window Window("Example");

    Thread::CreateThread((void(*)) WindowThread, 4096);

    Window.AddElement(UI::text::TextLabel({0,0}, Window.GetSize(), "Example text"));


    window.Render();

    while (true)
    {
        if(Exit)
        {
            break;
        }
    }
    return 0;
}