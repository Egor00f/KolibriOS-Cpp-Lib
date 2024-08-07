#include <kolibriLib/window/windowAttached.hpp>
#include <kolibriLib/system/thread.hpp>


using namespace KolibriLib;
using namespace window;

Window* arg;

Thread::Mutex lockARG;

void WindowFunc()
{
	Window* wndw = arg;
	lockARG.unlock();

	while(wndw->Handler() != OS::Events::Exit) { }
}

WindowAttached::WindowAttached(const Window_t &window)
{
	_wndw = new Window((Window)window);

	lockARG.waitPoint();
	lockARG.lock();
	arg = _wndw;

	Thread::CreateThread(WindowFunc, 4096); // Прошу господи лиж бы хватило
}

WindowAttached::~WindowAttached()
{
	delete _wndw;
}