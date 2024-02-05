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
        OS::Event event = window.Handler(); 

        switch (event)
        {
        case OS::Events::Exit:
            
            break;
        }
    }

    return 0;
}