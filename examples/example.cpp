#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	Window window("Example Window");

	UI::text::TextLabel textlabel({64, 64}, {100, 100}, "Hello World", 32);

	unsigned label = window.AddElement(textlabel);

	


	window.Redraw();

	bool exit = false;
	while (!exit)
	{
		Event event = window.Handler();
		if (event == Event::Exit)
		{
			exit = true;
		}
	}

	return 0;
}
