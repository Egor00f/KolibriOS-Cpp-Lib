#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
    window::Window window("Example");


    unsigned form = window.AddElement(UI::Form({64,64},{200, 100}, "text"));
    unsigned button = window.AddElement(UI::text::TextLabel({264, 64}, {100, 100}, "E"));

    window.Render();

    bool ext = false;
    while (ext)
    {
        OS::Event event = window.Handler();

        switch (event)
        {
        case OS::Events::Button:

            if(button = window.GetPressedButton())
            {
                childWindow::MessageBox(window.GetGetFromFrom(form), "You inputed in form:");
            }

            break;
        case OS::Events::Exit:
            ext = true;
            break;
        }
    }
    return 0;
}
