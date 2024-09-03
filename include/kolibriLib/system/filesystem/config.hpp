#ifndef __FILESYSTEM_CONFIG_HPP__
#define __FILESYSTEM_CONFIG_HPP__

#include <system_error>

namespace KolibriLib
{
	namespace filesystem
	{
		enum AttributeMasks
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
		std::error_code make_error_code(FilesystemErrors);
	} // namespace filesystem
	
} // namespace KolibriLib

namespace std
{
    template<>
    struct is_error_code_enum<KolibriLib::filesystem::FilesystemErrors>:
        true_type
    {};
}

#endif