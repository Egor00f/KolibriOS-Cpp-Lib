#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
    init();

    window::Window window("Main Window");

    unsigned ButtonID = window.AddElement(UI::buttons::Button({64, 64}, {100, 64}, "Button"));

    window.Render();

    bool ext = false;
    while (!ext)
    {
       OS::Event event = window.Handler();

        switch (event)
        {
        case /* constant-expression */:
            if(ButtonID == window.GetPressedButton())
            {
                childWindow::MessageBox("You pressed button", "Message");
            }
        case OS::Events::Exit:
            ext = true;
        }
    }
    
    return 0;
}