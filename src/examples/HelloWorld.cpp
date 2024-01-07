#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{
    init();
    window::Window window("Example Window");

    window.CreateText({64, 64}, {100, 100}, "This is text", 24, true);

    while(true)
    {
        unsigned Event = OS::WaitEvent();//Ждём пока не появится какой либо ивент

        switch (Event)
        {
        case KSYS_EVENT_REDRAW:
            window.Render();
            break;
        case KSYS_EVENT_BUTTON:
            switch (KolibriLib::UI::buttons::GetPressedButton())
            {
            case 1:
                return 0;
                break;
            
            default:
                break;
            }
            break;
        default:
            break;
        }
    }


    return 0;
}
