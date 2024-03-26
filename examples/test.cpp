/*test.cpp*/
#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	_ksys_debug_puts("test: init\n");
	init();
	_ksys_debug_puts("test: init done!\n");    
	window::Window window("Example Window");

	_ksys_debug_puts("cretae label\n");
	UI::text::TextLabel label(KolibriLib::Coord(0,0), window.GetWindowSize(), "Hello World!", UI::text::Fonts::Font(UI::text::Fonts::Micrhoma));

	_ksys_debug_puts("test: render lable\n");
	label.Render();

	_ksys_debug_puts("Start Main loop\n");
	bool exit = false;
	while (!exit)
	{
		_ksys_debug_puts("windiow handler\n");
		OS::Event event = window.Handler();
		_ksys_debug_puts("Handler not crash");
		if (event == OS::Events::Exit)
		{
			exit = true;
		}
	}
	return 0;
}
