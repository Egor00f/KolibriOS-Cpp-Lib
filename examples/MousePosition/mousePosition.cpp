#include <KolibriLib.hpp>

using namespace KolibriLib;

const char textRelative[] = "Relative mouse Pos: y: %i, x: %i";
const char textAbs[] = "Absolute mouse Pos: y: %i, x: %i";
TextLabel* MousePosAbs;
TextLabel* MousePosRelative;

void update()
{
	char buff[64];


	Coord mouseCoord = GetMousePositionOnSreen();

	sprintf(buff, textAbs, mouseCoord.y, mouseCoord.x);

	MousePosAbs->SetText(buff);


	mouseCoord = GetMousePositionInWindow();

	sprintf(buff, textAbs, mouseCoord.y, mouseCoord.x);

	MousePosRelative->SetText(buff);

	PrintDebug("\nText: \n");
	PrintDebug(MousePosRelative->GetText());
	PrintDebug("\n\n");
}

int main()
{
	SetEventMask(OS::Mask::DefaultEventMask || OS::Mask::AllMouseEvents);

	Window wnd("Mouse Pos");

	MousePosAbs = wnd.AddElement(TextLabel(
		UDim(0.2f, 0.2f),
		UDim(0.6f, 0.2f),
		"idk"));

	MousePosRelative = wnd.AddElement(TextLabel(
		UDim(0.2f, 0.4f),
		UDim(0.6f, 0.2f),
		"idk"));

	wnd.RenderAllElements();

	update();

	bool exit = false;
	while (!exit)
	{
		switch (wnd.Handler())
		{
		case Event::Exit:
			exit = true;
			break;
		case Event::Mouse:
			update();
			wnd.Redraw();
			break;
		default:
			break;
		}
	}
	
	return 0;
}