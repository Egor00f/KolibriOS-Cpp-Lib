#include <kolibriLib/system/os.hpp>
#include <stdlib.h>
#include <string.h>

using namespace KolibriLib;
using namespace OS;

Thread::PID KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args, filesystem::FilesystemErrors &ec, bool debug)

{
    int ret = _ksys_exec(AppName, const_cast<char*>(args.c_str()), debug);
	
	if(ret < 0)
	{
		ec = filesystem::FilesystemErrors::Successfully;
		return ret;
	}
	else
	{
		ec = (filesystem::FilesystemErrors)ret;
		return -1;
	}	

}

void KolibriLib::OS::Notify(const std::string &Title, const std::string &Text, notifyIcon icon, const notifyKey (&keys)[4])
{
	std::string a = "\"'" + Title + "\n" + Text + "' " + static_cast<char>(icon);
	
	if(!(keys[0] == notifyKey::NotSet))	// :)
	{
		a += keys[0];
		if (keys[1] != notifyKey::NotSet)
		{
			a += keys[1];
			if (keys[2] != notifyKey::NotSet)
			{
				a += keys[2];
				if (keys[3] != notifyKey::NotSet)
				{
					a += keys[3];
				}
			}
			
		}
	}
	

	_ksys_exec("/sys/@notify", const_cast<char*>(a.c_str()), false);
}

