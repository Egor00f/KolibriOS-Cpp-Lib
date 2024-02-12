#include "windowBase.hpp"

using namespace KolibriLib;

void KolibriLib::window::CreateWindow(const UI::Coord coord, const UI::Size size, const std::string &title, const Colors::Color WorkColor, const Colors::Color TitleColor, const uint32_t style)
{
    asm_inline(
        "int $0x40"
        :
        : "a"(0),
          "b"((coord.x << 16) | ((size.x - 1) & 0xFFFF)),
          "c"((coord.y << 16) | ((size.y - 1) & 0xFFFF)),
          "d"((style << 24) | (WorkColor.val & 0xFFFFFF)),
          "D"(title.c_str()),
          "S"(TitleColor)
        : "memory"
    );
}

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
