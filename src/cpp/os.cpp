#include <kolibriLib/system/os.hpp>
#include "os.hpp"

using namespace KolibriLib;
using namespace OS;

Colors::ColorsTable KolibriLib::OS::GetSystemColors()
{
    _ksys_get_system_colors(&sys_color_table);
    return sys_color_table;
}
Event KolibriLib::OS::WaitEvent(uint32_t TimeOut)
{
    if (TimeOut != 0)
    {
        return _ksys_wait_event_timeout(TimeOut);
    }
    else
    {
        return _ksys_check_event();
    }
}

int KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args)
    
{
    if (filesystem::Exist(AppName)) // Проверка на существование
    {
        char *a;
        strcat(a, const_cast<char*>(args.c_str()));
        return _ksys_exec(AppName.GetChars(), a);
    }
    else
    {
        return -1;
    }
}

void KolibriLib::Wait(int time)
{
    if(time == -1)
    {
        _ksys_thread_yield();
    }
    else    //Пох на на то что на проверки уходит время, нам всеравно нужно ждать
    {
        _ksys_delay(time);
    }
}
