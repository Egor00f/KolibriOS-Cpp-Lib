#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{

    KolibriLib::init();

    window::Window window("Main Window", window::DefaultWindowSize);

    window.CreateText({64, 64}, {100, 64}, "this is main Window", 24, true);


    KolibriLib::childWindow::MessageBox("This is child window", "child window");

    while (true)
    {
        unsigned Event = OS::WaitEvent(); // Ждём пока не появится какой либо ивент

        switch (Event)
        {
        case KSYS_EVENT_REDRAW:
            window.Render();
            break;
        case KSYS_EVENT_BUTTON:
            unsigned button = KolibriLib::UI::buttons::GetPressedButton();
            switch (button)
            {
            case 1:
                return 0;
                break;

            default:
                break;
            }
            break;
        }
    }

    return 0;
}