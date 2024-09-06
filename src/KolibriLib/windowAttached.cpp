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

	while(wndw->Handler() != OS::Event::Exit) { }
}

WindowAttached::WindowAttached(const Window_t &window)
{
	_wndw = new Window(window);

	lockARG.waitPoint();
	lockARG.lock();
	arg = _wndw;

	_pid = Thread::CreateThread(WindowFunc, 4096); // Прошу господи лижбы хватило
}

WindowAttached::~WindowAttached()
{
	Thread::TerminateThread(_pid);
	delete _wndw;
}

Thread::PID WindowAttached::GetPID() const
{
	return _pid;
}

UDim KolibriLib::window::WindowAttached::GetSize() const
{
	return UDim(GetWindowSize(_pid));
}

UDim KolibriLib::window::WindowAttached::GetCoord() const
{
	return UDim(GetWindowCoord(_pid));
}

Coord KolibriLib::window::WindowAttached::GetAbsoluteCoord() const
{
	return GetWindowCoord(_pid);
}

Size KolibriLib::window::WindowAttached::GetAbsoluteSize() const
{
	return GetWindowSize(_pid);
}

void KolibriLib::window::WindowAttached::SetPosition(const Pos &position)
{
	SetWindowPos(position, _pid);
}