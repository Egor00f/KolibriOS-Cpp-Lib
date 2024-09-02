#include <KolibriLib.hpp>

using namespace KolibriLib;


int main()
{

	Window wndw("Checbox example");

	auto frame = wndw.AddElement(UIElement(
		UDim(0.2f, 0.2f), 
		UDim(0.6f, 0.4f)));

	auto checkbox = wndw.AddElement(CheckBox(
		UDim(0.1f, 0.25f),		
		UDim(0.2f, 0.5f)
	));
	checkbox->SetParent(frame);
	
	auto textlabel = wndw.AddElement(TextLabel(
		UDim(0.3f, 0.0f),
		UDim(0.7f, 1.0f),
		"<- checkbox"
	));

	bool exit = false;
	while (!exit)
	{
		switch (wndw.Handler())
		{
		case Event::Exit:
			exit = true;
			break;
		case Event::Button:

			static bool lastState = false;

			if(checkbox->GetChecked() != lastState)
			{
				lastState = checkbox->GetChecked();

				OS::Notify("You change checkbox state", "just for you know");
			}

			break;
		default:
			break;
		}
	}
	

	return 0;
}