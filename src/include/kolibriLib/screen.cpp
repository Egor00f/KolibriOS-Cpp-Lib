#include "screen.hpp"

using namespace KolibriLib;

point<unsigned> KolibriLib::GetScreenSize()
{
    ksys_pos_t a = _ksys_screen_size();
    return (point<unsigned>){a.x, a.y};
}

Thread::Slot KolibriLib::ScreenPointAffiliation(point<unsigned> POINT)
{
    Thread::Slot s;
    __asm__ __volatile__ (
        "int $0x40"
        :"=a"(s)
        :"a"(34), "b"(POINT.x), "c"(POINT.y)
    );
    return s;
}

void KolibriLib::CenterCursor()
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(15)
    );
}
