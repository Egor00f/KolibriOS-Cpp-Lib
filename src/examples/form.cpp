#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
    window::Window window("Example");

    UI::Form f({64,64},{200, 100}, "text");

    unsigned form = window.CreateForm(f);
    unsigned button = window.CreateButton({264, 64}, {100, 100}, "E");

    while (true)
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
        }
        if(event == OS::Events::Exit)
        {
            break;
        }
    }
    return 0;
}