#ifndef __FILE_STATUS_HPP__
#define __FILE_STATUS_HPP__

namespace KolibriLib
{
	namespace filesystem
	{
		/// @brief
		/// @details определяет константы, указывающие тип файла или каталога, на который ссылается путь. Значения перечислителей различны.
		enum class file_type
		{
			/// @brief указывает на то, что статус файла еще не был оценен или при его оценке произошла ошибка
			none,

			/// @brief указывает на то, что файл не найден (это не считается ошибкой)
			not_found,

			/// @brief обычный файл
			regular,

			/// @brief каталог
			directory,
			symlink,
			block,
			character,
			fifo,
			socket,

			/// @brief файл существует, но его тип не может быть определен
			unknown,
		};

		enum class perms
		{

		};

		class file_status
		{
		public:
			file_status() noexcept : _type(file_type::none) {}

			file_status(const file_status &) noexcept = default;

			file_status(file_status &&) noexcept = default;

			file_status &operator=(const file_status &other) noexcept = default;
			file_status &operator=(file_status &&other) noexcept = default;

			file_type type() const noexcept;

			void type(filesystem::file_type type) noexcept;

			filesystem::perms permissions() const noexcept;
			void permissions(filesystem::perms perm) noexcept;

		private:
			file_type _type;
			perms _perms;
		};
	} // namespace filesystem
	
} // namespace KolibriLib


#endif