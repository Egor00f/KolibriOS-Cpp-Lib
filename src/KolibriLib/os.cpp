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
        return _ksys_exec(AppName, (char*)args.c_str(), debug);
    }
    return -1;
}

void KolibriLib::OS::Notify(const std::string &Title, const std::string &Text, notifyIcon icon, const notifyKey (&keys)[4])
{
	std::string a = "\"'" + Title + "\n" + Text + "' " + (char)icon;
	
	if(!(keys[0] == (notifyKey)0))	// :)
	{
		a += keys[0];
		if (!(keys[1] == (notifyKey)0))
		{
			a += keys[1];
			if (!(keys[2] == (notifyKey)0))
			{
				a += keys[2];
				if (!(keys[3] == (notifyKey)0))
				{
					a += keys[3];
				}
			}
			
		}
	}
	

	_ksys_exec("/sys/@notify", (char *)a.c_str(), false);
}