#include "screen.hpp"

using namespace KolibriLib;

UI::Size KolibriLib::GetScreenSize()
{
    ksys_pos_t a = _ksys_screen_size();
    return {(int)a.x, (int)a.y};
}

Thread::Slot KolibriLib::ScreenPointAffiliation(UI::Coord POINT)
{
    Thread::Slot s;
    __asm__ __volatile__ (
        "int $0x40"
        :"=a"(s)
        :"a"(34), "b"(POINT.x), "c"(POINT.y)
    );
    return s;
}

UI::Size KolibriLib::GetBackgroundImageSize()
{
    UI::Size p;
    unsigned a;
    asm_inline(
        "int $0x40"
        :"=a"(a)
        :"a"(39), "b"(1)
    );
    p.x = (a >> 16);
    p.y = a;
    return p;
}

Colors::Color KolibriLib::ReadBackgroungImagePoint(point<unsigned> Point)
{
    Colors::Color c;

    //Смещение
    unsigned s = GetBackgroundImageSize().x * (Point.y -1) + Point.x;   //я думаю, что изображение это двумерный массив

    asm_inline(
        "int $0x40"
        :"=a"(c.val)
        :"a"(39), "b"(2), "c"(s)
    );

    return c;
}
