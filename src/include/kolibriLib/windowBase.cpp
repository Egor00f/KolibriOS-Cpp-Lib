#include "windowBase.hpp"

using namespace KolibriLib;

void KolibriLib::window::UnfocusWindow(Thread::Slot slot)
{
    _ksys_unfocus_window(slot);
}

void KolibriLib::window::FocusWindow(Thread::Slot slot)
        {
            _ksys_focus_window(slot);
        }

Thread::Slot KolibriLib::window::GetActiveWindow()
{
    Thread::Slot s;
    asm_inline(
        "int $0x40"
        :"=a"(s)
        :"a"(18), "b"(7)
    );
    return s;
}

void KolibriLib::window::MinimizeWindow()
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(10)
    );
}

void KolibriLib::window::MinimizeAllWindows()
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(23)
    );
}

int KolibriLib::window::GetWindowPos()
{
    int a;
    asm_inline(
        "int $0x40"
        :"=a"(a)
        :"a"(18), "b"(25), "c"(1)
    );
    return a;
}

bool KolibriLib::window::SetWindowPos(int pos, Thread::PID pid)
{
    bool a;
    asm_inline(
        "int $0x40"
        : "=a"(a)
        : "a"(18), "b"(25), "c"(2), "d"(pid), "S"(pos)
        );
    return a;
}

unsigned KolibriLib::window::GetSkinHeight()
{
    return _ksys_get_skin_height();
}
