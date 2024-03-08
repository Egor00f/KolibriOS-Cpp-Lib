#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{

    KolibriLib::init();

    window::Window window("Main Window");

    window.AddElement(UI::text::TextLabel({64, 64}, {100, 64}, "This is main Window", 24, true));

    window.Render();


    KolibriLib::childWindow::MessageBox("This is child window", "child window");

    while (true)
    {
        OS::Event event = window.Handler(); 

        switch (event)
        {
        case OS::Events::Exit:
            break;
        }
    }

    return 0;
}

