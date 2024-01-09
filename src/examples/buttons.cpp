#include <KolibriLib.hpp>

using namespace KolibriLib;



int main()
{

    KolibriLib::init();

    window::Window window("Main Window", window::DefaultWindowSize);

    unsigned ButtonID = window.CreateButton({64, 64}, {100, 64}, "Button");

    while (true)
    {
        unsigned Event = window.Handler();

        switch (Event)
        {
        case KSYS_EVENT_BUTTON:

            unsigned a = window.GetPressedButton();
            
            if(a == ButtonID)
            {
                childWindow::MessageBox("You pressed button", "You pressed button");
            }
            
            break;
        }

        if(EXIT)
        {
            break;
        }
    }
    
    return EXITCODE;
}