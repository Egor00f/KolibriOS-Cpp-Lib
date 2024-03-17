/*test.cpp*/
#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	_ksys_debug_puts("test: start!");
	_ksys_debug_puts("test: init");
	init();
	_ksys_debug_puts("test: init done!");    
	window::Window window("Example Window");

	window.AddElement(UI::text::TextLabel({0, 0}, window.GetWindowSize(), "Hello World!", UI::text::Fonts::Font(UI::text::Fonts::Micrhoma)));
	
	bool exit = false;
	while (!exit)
	{
		OS::Event event = window.Handler();
		if (event == OS::Events::Exit)
		{
			exit = true;
		}
	}
	return 0;
}
