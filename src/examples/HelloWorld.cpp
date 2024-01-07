#include <KolibriLib.hpp>

using namespace KolibriLib;

void RenderWindow()
{
    point mouse = mouse::GetMousePositionInWindow();
    window::StartRedraw();
    window::DrawWindow(mouse, window::DefaultWindowSize, "Hello World!");


    UI::text::DrawText("Hello World!", {200, 200});

    window::EndRedraw();
}

int main()
{
    KolibriLib::window::initWindow();
    RenderWindow();

    while(true)
    {
        unsigned Event = OS::WaitEvent();//Ждём пока не появится какой либо ивент

        switch (Event)
        {
        case KSYS_EVENT_REDRAW:
            RenderWindow();
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
