#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
    window::Window window("Example");

    unsigned form = window.CreateForm({64, 64}, {100, 64}, "text...");
    unsigned button = window.CreateButton({164, 64}, {64,64}, "E");

    while (true)
    {
        unsigned Event = window.Handler();

        switch (Event)
        {
        case KSYS_EVENT_BUTTON:

            if(button = window.GetPressedButton())
            {
                childWindow::MessageBox(window.GetTextFromForm(form), "You inputed in form:");
            }

            break;
        }
        if(KolibriLib::EXIT)
        {
            break;
        }
    }
    return EXITCODE;
}