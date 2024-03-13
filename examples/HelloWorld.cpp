#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{
    init();
    
    window::Window window("Example Window");

    window.AddElement(UI::text::TextLabel({0, 0}, window.GetWindowSize(), "Hello World!", UI::text::Fonts::Font(UI::text::Fonts::Micrhoma))); // Текст на всё окно

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
