#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	Window window("Example Window");

	TextLabel *textlabel = window.AddElement(TextLabel({0, window::GetSkinHeight()}, window.GetWindowSize(), "Hello World", 32)).second;

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
