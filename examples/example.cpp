#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	window::Window window("Example Window");


	UI::text::TextLabel label(KolibriLib::Coord(64, 64), {200, 200},
						"Hello World!", UI::text::Fonts::DefaultFont);

	label.Render();


	_ksys_debug_puts("Start Main loop\n");
	bool exit = false;
	while (!exit)
	{
		OS::Event event = window.Handler();
		UI::text::DrawText("Hello Horld", {64, 64}, UI::text::Fonts::DefaultFont);
		if (event == OS::Events::Exit)
		{
			exit = true;
		}
	}

	return 0;
}
