#include <KolibriLib.hpp>

using namespace KolibriLib;

int main()
{
	init(); 
	Window window("Example Window");

	Window::ElementNumber textlabel = window.AddElement(TextLabel(UDim(0, 0, 0, 0), UDim(0.6, 0, 1, 0), "Hello World", 32));

	Window::ElementNumber button = window.AddElement(Button(UDim(0.6, 0, 0.8, 0), UDim(0.2, 0, 0.1, 0)));

	Button tmp = *((Button*)window.GetElement(button).pointer);

	tmp.SetText("Button");

	window.SetElement(button, tmp);

	window.Redraw();

	bool exit = false;
	while (!exit)
	{
		Event event = window.Handler();
		
		switch (event)
		{
		case Event::Exit:
			exit = true;
			break;
		case Event::Button:
			if(window.GetPressedButton() == ((Button*)window.GetElement(button).pointer)->GetId())
			{
				_ksys_debug_puts("ButtonPressed");
			}
		default:
			break;
		}
	}

	return 0;
}
