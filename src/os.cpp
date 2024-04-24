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

void Notify(const std::string &Title, const std::string &Text, notifyIcon icon, std::vector<notifyKey> keys)
{
	std::string a = "\"'" + Title + "\n" + Text + "' " + (char)icon;
	for(short i = 0; i < keys.size(); i++)
    {
		a += (" -" + (char)keys[i]);
	}
	_ksys_exec("/sys/@notify", (char *)a.c_str(), false);
}