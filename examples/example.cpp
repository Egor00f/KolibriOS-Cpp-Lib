#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	window::Window window("Example Window");

	UI::text::TextLabel label(KolibriLib::Coord(0, 0), window.GetWindowSize(),
						"Hello World!", UI::text::Fonts::Font(UI::text::Fonts::Micrhoma));

	label.Render();


	_ksys_debug_puts("Start Main loop\n");
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
