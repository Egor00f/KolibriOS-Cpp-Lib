#include <KolibriLib.hpp>

// АХТУНГ!!!!
using namespace KolibriLib;

int main()
{
	Window* wndw = new Window (
		"Example Window",           // Заголовок окна
		window::DefaultWindowSize,  // Размер окна
		window::DefaultWindowCoord, // Положение окна
		Globals::SystemColors       // Цвета окна
	);

	// Добавление текстовой метки
	auto label = wndw->AddElement(TextLabel(
		                            UDim(0.0f, 0, 0.0f, 0), 	// Координаты текстовой метки (самый левый верхний угол окна)
									UDim(0.6f, 0, 1.0f, 0), 	// Рамер текстовой метки (3/5 ширины окна и в полную высоту окна)
									"Hello World",
									{32, 36}           	// Размер символов 32x36
								)
					);

	// Добавление кнопки
	TextButton* button = wndw->AddElement(TextButton(UDim(0.4f, 0, 0.4f, 0), UDim(0.2f, 0, 0.2f, 0)));

	// Отрисовка всех элементов, чтоб они были видны
	wndw->RenderAllElements();

	bool exit = false;
	while (!exit)
	{

		// Вызов обработчика окна
		Event event = wndw->Handler();
		
		switch (event)
		{
		case Event::Exit: // Если был нажат крестик
			exit = true; 
			break;
		case Event::Button:
			if(wndw->GetPressedButton() == button->GetId())
			{
				_ksys_debug_puts("You Press Button");
				OS::Notify("You Press Buttons", "just example");
			}
		default:
			break;
		}
	}

	delete wndw;

	return 0;
}
