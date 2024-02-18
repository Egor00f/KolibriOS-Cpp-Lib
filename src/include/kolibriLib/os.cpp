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
        strcat(a, const_cast<char*>(args.c_str()));
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

void KolibriLib::OS::SpeakerSwitch()
{
    asm_inline(
        "int $0x40"
        ::"a"(18), "b"(8), "c"(2)
    );
}

unsigned KolibriLib::OS::FreeMem()
{
    unsigned a;
    asm_inline(
        "int $0x40"
        : "=a"(a)
        : "a"(18), "b"(16));
    return a;
}

unsigned KolibriLib::OS::AllMem()
{
    unsigned a;
    asm_inline(
        "int $0x40"
        :"=a"(a)
        :"a"(18), "b"(17)
    );
    return a;
}

int KolibriLib::OS::GetLang()
{
    int a;
    asm_inline(
        "int $0x40"
        :"=a"(a)
        :"a"(26), "b"(5)
    );
    return a;
}

bool KolibriLib::OS::SpeakerStatus()
{
    bool a;
    asm_inline(
        "int $0x40"
        :"=a"(a)
        :"a"(18), "b"(8), "c"(1)
    );
    return !a;
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
