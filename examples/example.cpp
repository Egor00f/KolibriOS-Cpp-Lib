#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	Window window("Example Window");

	TextLabel *textlabel = window.AddElement(TextLabel(UDim(0,0,0,0), UDim(1,0,1,0), "Hello World", 32)).second;

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
