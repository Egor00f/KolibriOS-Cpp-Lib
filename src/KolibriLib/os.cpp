#include <kolibriLib/system/os.hpp>
#include <stdlib.h>
#include <string.h>

using namespace KolibriLib;
using namespace OS;

Colors::ColorsTable KolibriLib::OS::GetSystemColors()
{
	/*
	Colors::ColorsTable *buff = (Colors::ColorsTable*) malloc(sizeof(Colors::ColorsTable));

	asm_inline(
		"int $0x40"
		::"a"(47), "b"(3), "c"(buff), "d"(sizeof(Colors::ColorsTable))
	);

	Colors::ColorsTable ret(*buff);
    free(buff);
	*/

	ksys_colors_table_t a;

	_ksys_get_system_colors(&a);

	return Colors::ColorsTable(a);
}

Thread::PID KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args, bool debug)

{
    if (filesystem::Exist(AppName)) // Проверка на существование
    {
        char *a = "";
        strcat(a, args.c_str());
        return _ksys_exec(AppName, a, debug);
    }
    return -1;
}

void Notify(const std::string &Title, const std::string &Text, notifyIcon icon, const std::vector<notifyKey> &keys)
{
	std::string a = "\"'" + Title + "\n" + Text + "' " + (char)icon;
	for(short i = 0; i < keys.size(); i++)
    {
		a += (" -" + (char)keys[i]);
	}
	_ksys_exec("/sys/@notify", (char *)a.c_str(), false);
}