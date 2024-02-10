#include "mouse.hpp"

using namespace KolibriLib;

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
