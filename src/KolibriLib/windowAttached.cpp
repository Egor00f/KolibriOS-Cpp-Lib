#include <kolibriLib/window/windowAttached.hpp>
#include <kolibriLib/system/thread.hpp>


using namespace KolibriLib;
using namespace window;

void* arg;

Thread::Mutex lockARG;

void WindowFunc()
{
	Window* wndw = new Window(*(Window_t*)arg);
	arg = wndw;

	lockARG.unlock();

	while(wndw->Handler() != OS::Event::Exit) { }
}

WindowAttached::WindowAttached(const Window_t &window)
{
	lockARG.waitPoint();
	lockARG.lock();
	arg = (void*)&window;	
	_pid = Thread::CreateThread(WindowFunc, 4096); // Прошу господи лижбы хватило
	
	lockARG.waitPoint();

	_wndw = (Window*)arg;
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

void KolibriLib::window::WindowAttached::Focus() const
{
	window::FocusWindow(Thread::GetThreadSlot(_pid));
}

void KolibriLib::window::WindowAttached::Unfocus() const
{
	window::UnfocusWindow(Thread::GetThreadSlot(_pid));
}

UI::buttons::ButtonsIDController *KolibriLib::window::WindowAttached::GetButtonIDController() const
{
	return _wndw->GetButtonIDController();
}
