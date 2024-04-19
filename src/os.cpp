#include <kolibriLib/system/os.hpp>

using namespace KolibriLib;
using namespace OS;

int KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args, bool debug)
{
    if (filesystem::Exist(AppName)) // Проверка на существование
    {
        char *a;
        strcat(a, args.c_str());
        return _ksys_exec(AppName, a, debug);
    }
    return -1;
}
