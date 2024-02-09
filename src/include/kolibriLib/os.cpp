#include "os.hpp"

using namespace KolibriLib;
using namespace OS;

Colors::ColorsTable KolibriLib::OS::GetSystemColors()
{
    _ksys_get_system_colors(&sys_color_table);
    return sys_color_table;
}

OS::Event KolibriLib::OS::WaitEvent()
{
    return _ksys_wait_event();
}

OS::Event KolibriLib::OS::WaitEvent(uint32_t TimeOut)
{
    _ksys_wait_event_timeout(TimeOut);
}

OS::Event KolibriLib::OS::CheckEvent()
{
    return _ksys_check_event();
}

int KolibriLib::OS::Exec(const filesystem::Path& AppName, const std::string& args)
{
    if (filesystem::Exist(AppName)) // Проверка на существование
    {
        char *a;
        strcat(a, args.c_str());
        return _ksys_exec(AppName.GetChars(), a);
    }
    else
    {
        return -1;
    }
}


ksys_time_t KolibriLib::OS::GetTime()
{
    return _ksys_get_time();
}

void KolibriLib::Wait(unsigned time)
{
    _ksys_delay(time);
}
