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
