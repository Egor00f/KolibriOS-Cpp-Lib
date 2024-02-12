#include "mouse.hpp"

using namespace KolibriLib;
using namespace mouse;

point<int> KolibriLib::mouse::GetMousePositionOnSreen()
{
    ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_SCREEN_POS);

    return (KolibriLib::point<int>){a.x, a.y};
}

point<int> KolibriLib::mouse::GetMousePositionInWindow()
{
    ksys_pos_t a = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS);

    return (point<int>){a.x, a.y};
}

uint32_t KolibriLib::mouse::GetMouseButtons()
{
    return _ksys_get_mouse_buttons();
}

uint32_t KolibriLib::mouse::GetMouseWheels()
{
    return _ksys_get_mouse_wheels();
}

void KolibriLib::mouse::EmulateMouse(uint8_t m)
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(19), "c"(5), "d"(m)
    );
}

void KolibriLib::mouse::CenterCursor()
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(15)
    );
}

CursorHandle KolibriLib::mouse::LoadCursor(filesystem::Path path)
{
    return _ksys_load_cursor((void*)path.GetChars(), KSYS_CURSOR_FROM_FILE);
}

CursorHandle KolibriLib::mouse::LoadCursor(void *ptr)
{
    return _ksys_load_cursor(ptr, KSYS_CURSOR_FROM_MEM);
}

CursorHandle KolibriLib::mouse::SetCursor(CursorHandle handle)
{
    return _ksys_set_cursor(handle);
}

void KolibriLib::mouse::DeleteCursor(CursorHandle handle)
{
    _ksys_delete_cursor(handle);
}


