#include <kolibriLib/childWindow.hpp>

using namespace KolibriLib;
using namespace childWindow;

void RenderMessageWindow(void*)
{
    std::string _Message    = Message;
    std::string _Title      = Title;

    window::Window window(_Title, {256,128});

    UI::Size WindowSize = window.GetSize();

    window.AddElement(UI::text::TextLabel({(int)window.GetMargin(), (int)window.GetMargin()}, {WindowSize.x, WindowSize.y / 2}, _Message, 16));

    const unsigned ButtonSize = 40;

    UI::buttons::Button OK({(int)WindowSize.x - (int)window.GetMargin(), WindowSize.y / 2}, {ButtonSize, WindowSize.y / 2}, 0);
    OK.Add("OK");

    unsigned ok = window.AddElement(OK);
    
    OK.~Button();

            

    window.Render();
    while (true)
    {
        OS::Event event = window.Handler();
        if(event = OS::Events::Exit)
        {
            window.~Window();
            _ksys_exit();
        }
    }
}

void KolibriLib::childWindow::MessageBox(const std::string &_Message, const std::string &_Title)
{
    while (true)
    {
        if (!Used) // Проверка на то создают ли другие потоки ещё MessageWindow.
        {          // Это так потому что глобальная переменная Newindex одна на всех
            Used = true;

            Message = _Message;
            Title = _Title;

            Thread::CreateThread(RenderMessageWindow, 8192);    //Выделил памяти чуть больше, чтоб точно хватило

            Used = false; // Я всё, заКОНЧИЛ. Свободно!
            break;;
        }
        else // если занято то ждём
        {
            _ksys_thread_yield();
        }
    }
}
