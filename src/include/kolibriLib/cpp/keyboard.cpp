#include <kolibriLib/input/keyboard.hpp>

using namespace KolibriLib;

char KolibriLib::keyboard::CheckKeyboard()
{
    return _ksys_get_key().code;
}

unsigned KolibriLib::keyboard::GetControlKey()
{
    return _ksys_get_control_key_state();
}

bool KolibriLib::keyboard::InstallHotKey(uint16_t controlkeys)
{
    return !_ksys_set_sys_hotkey(0, controlkeys);
}
