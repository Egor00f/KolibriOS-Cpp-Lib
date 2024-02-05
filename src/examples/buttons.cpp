#include <KolibriLib.hpp>

using namespace KolibriLib;





int main()
{

    KolibriLib::init();

    window::Window window("Main Window", window::DefaultWindowSize);

    unsigned ButtonID = window.CreateButton({64, 64}, {100, 64}, "Button");

    window.Render();

    while (true)
    {
       OS::Event event = window.Handler();

        if(event == OS::Events::Button)        
        {
            if(ButtonID == window.GetPressedButton())
            {
                childWindow::MessageBox("You pressed button", "Message");
            }
        }

        if(event == OS::Events::Exit)
        {
            break;
        }
    }
    
    return 0;
}