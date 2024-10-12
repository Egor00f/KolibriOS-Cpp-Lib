#ifndef __SYSTEM_VIRTDISK_HPP__
#define __SYSTEM_VIRTDISK_HPP__

#include <kolibriLib/filesystem/filesystem.hpp>
#include <kolibriLib/system/os.hpp>
#include <cstdio>

namespace KolibriLib
{
	/**
	 * @brief Работа с виртульными дисками
	 * @details По приколу, пусть будет
	 */
	namespace Virtdisk
	{
		enum class ImageType
		{
			idk,
			raw,
			img,
			iso
		};

		/**
		 * @brief Добавляет рамдиск через прогу virtdisk
		 * @param DiskName путь до файла
		 * @param SectorSize размер сектора
		 * @param type тип
		 * @param ReadOnly 
		 * @return 
		 */
		inline Thread::PID AddDisk(const filesystem::path& DiskName, int SectorSize = -1, ImageType type = ImageType::idk, bool ReadOnly = false)
		{
			std::string args = "-a " + static_cast<std::string>(DiskName);

			if(SectorSize != -1)
			{
				char buff[32];
				std::sprintf(buff, " -s %i", SectorSize);
				args += buff;
			}

			if(type != ImageType::idk)
			{
				args += " -t ";
				switch (type)
				{
				case ImageType::img:
					args += "img";
					break;
				case ImageType::iso:
					args += "iso";
					break;
				case ImageType::raw:
					args += "raw";
					break;
				}
			}

			args += " -f";
			if(ReadOnly)
				args += "ro";
			else
				args += "rw";

			return OS::Exec("/sys/virtdisk", args);
		}
	} // namespace Virtdisk
	
} // namespace KolibriLib


#endif // __SYSTEM_VIRTDISK_HPP__