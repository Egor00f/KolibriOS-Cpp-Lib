#include <KolibriLib.hpp>

// АХТУНГ!!!!
using namespace KolibriLib;

int main()
{
	Window* wndw = new Window (     // указатель не обязятельно, но можно
		"Example Window"            // Заголовок окна
	);

	// Добавление текстовой метки
	auto bar = wndw->AddElement(ProgressBar(
		UDim(0.2f, 0.2f),
		UDim(0.2f, 0.6f)
	));

	// Добавление кнопки
	TextButton* button = wndw->AddElement(TextButton(UDim(0.6f, 0, 0.4f, 0), UDim(0.2f, 0, 0.2f, 0), "Press Me"));

	// Отрисовка всех элементов, чтоб они были видны
	wndw->RenderAllElements();

	bool exit = false;
	while (!exit)
	{
		// Вызов обработчика окна
		Event event = wndw->Handler();
		
		switch (event)
		{
		case Event::Exit: // Если был нажата кнопка закрытия окна

			exit = true; 
			break;
		case Event::Button:

			if(wndw->GetPressedButton() == button->GetId())
			{
				bar->AddFill(1);
			}

			break;
		default:
			break;
		}		
	}

	delete wndw;

	return 0;
}
