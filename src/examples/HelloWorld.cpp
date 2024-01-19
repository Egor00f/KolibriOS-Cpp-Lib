#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{
    init();
    window::Window window("Example Window");

    window.CreateText({64, 64}, {100, 100}, "Hello World!", 24, true);

    while(true)
    {
        OS::Event event = window.Handler();
        if (event = OS::Events::Exit)
        {
            break;
        }
    }

    return 0;
}
