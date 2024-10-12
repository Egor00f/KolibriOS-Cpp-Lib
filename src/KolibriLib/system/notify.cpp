#include <kolibriLib/system/notify.hpp>
#include <kolibriLib/system/os.hpp>

using namespace KolibriLib;

void KolibriLib::OS::Notify(const std::string &Text, notifyIcon icon, const notifyKey (&keys)[4])
{
	std::string a = "\"'" + Text + "' " + static_cast<char>(icon);

	if (!(keys[0] == notifyKey::NotSet)) // :) тут их всего четыре, можно и ручками
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

	OS::Exec("/sys/@notify", a, false);
}