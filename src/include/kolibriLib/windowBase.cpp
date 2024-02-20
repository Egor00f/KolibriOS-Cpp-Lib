#include "windowBase.hpp"

using namespace KolibriLib;


UI::Coord KolibriLib::window::GetWindowCoord()
{
    return mouse::GetMousePositionOnSreen() - mouse::GetMousePositionInWindow();
}