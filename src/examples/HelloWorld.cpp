#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{
    init();
    window::Window window("Example Window");

    window.CreateText({64, 64}, {100, 100}, "This is text", 24, true);

    while(true)
    {
        window.Handler();
        if(EXIT)
        {
            break;
        }
    }

    return EXITCODE;
}
