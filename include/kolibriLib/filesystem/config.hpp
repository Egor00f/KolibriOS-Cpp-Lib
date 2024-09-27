#ifndef __FILESYSTEM_CONFIG_HPP__
#define __FILESYSTEM_CONFIG_HPP__

namespace KolibriLib
{
	namespace filesystem
	{
		enum class AttributeMasks
		{
			OnlyRead = 1,
			Hide = 2,
			System = 4,
			Label = 8,
			Dir = 0x10,
			NoArchive = 0x20
		};

		/// @brief Системные ошибки
		enum class FilesystemErrors
		{
			/// @brief успешно
			Successfully = 0,

			/// @brief функция не поддерживается для данной файловой системы
			NotSupport = 2,

			/// @brief неизвестная файловая система
			UnklownFileSystem = 3,

			/// @brief файл не найден
			NotFound = 5,

			/// @brief EOF, файл закончился
			EndOfFile = 6,

			/// @brief указатель вне памяти приложения
			ptrOutsideApp = 7,

			/// @brief диск заполнен
			DiskIsFull = 8,

			/// @brief ошибка файловой системы
			FSError = 9,

			/// @brief доступ запрещён
			AccessDenied = 10,

			/// @brief ошибка устройства
			DeviceError = 11,

			/// @brief файловой системе недостаточно оперативной памяти
			OsHaventRam = 12
		};
	} // namespace filesystem
	
} // namespace KolibriLib

#endif