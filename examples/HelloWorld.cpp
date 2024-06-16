#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{
    init();
    
    window::Window window("Example Window");

    window.AddElement(); // Текст на всё окно

    while (true)
    {
        
        OS::Event event = window.Handler();
        if (event == OS::Events::Exit)
        {
            break;
        }
    }
    return 0;
}
