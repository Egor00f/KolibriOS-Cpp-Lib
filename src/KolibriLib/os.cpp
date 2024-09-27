#include <kolibriLib/system/os.hpp>
#include <cstdlib>
#include <cstring>

using namespace KolibriLib;
using namespace OS;

Thread::PID KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args, filesystem::FilesystemErrors &ec, bool debug)

{
	int ret = _ksys_exec(AppName.c_str(), const_cast<char *>(args.c_str()), debug);

	if (ret < 0)
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

Thread::PID KolibriLib::OS::Exec(const filesystem::Path &AppName, const std::string &args, bool debug)
{
	filesystem::FilesystemErrors ec;
	return Exec(AppName, args, ec, debug);
}

void KolibriLib::OS::Notify(const std::string &Title, const std::string &Text, notifyIcon icon, const notifyKey (&keys)[4])
{
	std::string a = "\"'" + Title + "\n" + Text + "' " + static_cast<char>(icon);

	if (!(keys[0] == notifyKey::NotSet)) // :)
	{
		a += static_cast<char>(keys[0]);
		if (keys[1] != notifyKey::NotSet)
		{
			a += static_cast<char>(keys[1]);
			if (keys[2] != notifyKey::NotSet)
			{
				a += static_cast<char>(keys[2]);
				if (keys[3] != notifyKey::NotSet)
				{
					a += static_cast<char>(keys[3]);
				}
			}
		}
	}

	Exec("/sys/@notify", a, false);
}

CoreVersion KolibriLib::OS::GetCoreVersion()
{
	// Реальнаяч структура
	struct RealCoreVersion
	{
		union
		{
			// Версия
			std::uint32_t version;
			struct
			{
				std::uint8_t a;
				std::uint8_t b;
				std::uint8_t c;
				std::uint8_t d;
			};
		};

		// Зарезервированно
		std::uint8_t reserved;

		/// @brief Ревизия
		std::uint16_t Rev;
	};

	RealCoreVersion *data = (RealCoreVersion*)std::malloc(16);

	asm_inline(
		"int $0x40" ::"a"(18), "b"(13), "c"(data));

	CoreVersion p;

	p.version = data->version;
	p.Rev = data->Rev;

	std::free(data);

	return p;
}