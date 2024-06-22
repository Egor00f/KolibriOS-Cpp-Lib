#include <KolibriLib.hpp>

// АХТУНГ!!!!
using namespace KolibriLib;

int main()
{
	//Инициализация библиотеки
	init(); 

	Window window(
		"Example Window",        	// Заголовок окна
		window::DefaultWindowSize,	// Размер окна
		GetSystemColors(),       	// Цвета окна
		true                     	// Можно ли изменять размер окна пользователю
	);

	// Добавление текстовой метки
	Window::ElementNumber textlabel = window.AddElement(TextLabel(
		                                                          UDim(0, 0, 0, 0), 	// Координаты текстовой метки (самый левый верхний угол окна)
																  UDim(0.6, 0, 1, 0), 	// Рамер текстовой метки (3/5 ширины окна и в полную высоту окна)
																  "Hello World",
																  {32, 36}           	// Размер символов 32x36
																  ));

	// Добавление кнопки
	Window::ElementNumber button = window.AddElement(Button(UDim(0.6, 0, 0.8, 0), UDim(0.2, 0, 0.1, 0)));

	// Получение кнопки обратно
	Button tmp(*(Button*)window.GetElement(button));

	// изменение текста в полученной кнопке
	tmp.SetText("Button");

	// Замена кнопки в окне на изменнёную
	window.SetElement(button, tmp);

	// больше не пригодится
	tmp.~Button();
	
	// Отрисовка окна
	window.Render(window::DefaultWindowCoord);

	bool exit = false;
	while (!exit)
	{

		// Вызов обработчика окна
		Event event = window.Handler();
		
		switch (event)
		{
		case Event::Exit:
			exit = true;
			break;
		case Event::Button:
			if(window.GetPressedButton() == ((Button*)window.GetElement(button))->GetId())
			{
				childWindow::MessageBox("button pressed", "Message");
			}
		default:
			break;
		}
	}

	return 0;
}
