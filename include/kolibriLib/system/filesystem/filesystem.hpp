#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <string>
#include <ctime>

#include "config.hpp"
#include "file_status.hpp"


namespace KolibriLib
{
    /// @brief Работа с файлами
    /// @paragraph подражает std::filesystem из C++17, но им не является
    /// @paragraph Херня какето
    namespace filesystem
    {
        
        enum class copy_options
        {
            /// @brief 
            none,
            skip_existing,
            overwrite_existing,
            update_existing,
            recursive,
        };

        /// @brief Путь до файла/папки
        class Path
        {
            public:
                Path() = default;

                /// @brief Конструктор
                /// @param path Путь
                Path(const char* path);

                /// @brief Конструктор
                /// @param path путь
                Path(const std::string& path);

                Path(const Path&) = default;

                Path(Path&&) = default;

                ~Path() = default;

                /// @brief Длинна строки
                std::size_t length() const;

                operator const char*() const;
                operator std::string() const;
                
                Path &operator / (const Path &a);
                Path &operator / (const std::string &a);
                Path &operator + (const Path &a);
                Path &operator + (const std::string &a);
                Path &operator = (const Path &a) = default;
                Path &operator = (const std::string &a);

                bool operator == (const Path &a) const;
                bool operator != (const Path &a) const;

                bool operator == (const std::string &a) const;
                bool operator != (const std::string &a) const;
            private:
                std::string _string;
        };

        /// @brief Штоб название было как в std::filesystem, а то менять в куче файлов название не очень
        using path = Path;

        using file_time_type = std::tm;

        class directory_entry
        {
        public:
            directory_entry() noexcept = default;
            directory_entry(const directory_entry &) = default;
            directory_entry( directory_entry&& ) noexcept = default;
            explicit directory_entry( const filesystem::path& p );
            
            /// @brief 
            /// @param p 
            /// @param ec 
            directory_entry( const filesystem::path& p, FilesystemErrors& ec );

            ~directory_entry() = default;

            void assign( const filesystem::path& p );
            void assign( const filesystem::path& p, FilesystemErrors& ec );

            void replace_filename( const filesystem::path& p );
            void replace_filename( const filesystem::path& p, FilesystemErrors& ec );

            void refresh();
            void refresh( FilesystemErrors& ec ) noexcept;

            directory_entry &operator=(const directory_entry &other) = default;
            directory_entry &operator=(directory_entry &&other) noexcept = default;

        private:
            filesystem::path _path;
            std::uintmax_t file_size;
            file_time_type _last_mod_time;
        };

        /// @brief Получить размер файла
        /// @param p путь до файла
        /// @return размер файла
        /// @throw если ошибка кидаеется исключение с кодом ошибки
        std::uintmax_t file_size(const Path &p);

        /// @brief Получить размер файла
        /// @param p путь до файла
        /// @param ec ссылка на код ошибки
        /// @return размер файла
        std::uintmax_t file_size(const Path &p, FilesystemErrors& ec ) noexcept;

        /// @brief 
        /// @param p 
        /// @param new_size 
        void resize_file(const path &p, std::uintmax_t new_size);

        /// @brief 
        /// @param p 
        /// @param new_size 
        /// @param ec
        void resize_file(const filesystem::path &p, std::uintmax_t new_size, FilesystemErrors &ec) noexcept;

        bool copy_file(const filesystem::path &from, const filesystem::path &to);
        bool copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options);
        bool copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options, FilesystemErrors &ec);

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool exists(const Path &p);
        bool exists(const filesystem::path &p, FilesystemErrors &ec) noexcept;

        void rename(const filesystem::path &old_p, const filesystem::path &new_p);
        void rename( const filesystem::path& old_p, const filesystem::path& new_p, FilesystemErrors& ec ) noexcept;

        bool is_directory( filesystem::file_status s ) noexcept;
        bool is_directory(const filesystem::path &p);
        bool is_directory( const filesystem::path& p, FilesystemErrors& ec ) noexcept;

        filesystem::file_time_type last_write_time( const filesystem::path& p );
        filesystem::file_time_type last_write_time(const filesystem::path &p, FilesystemErrors &ec) noexcept;

        /// @brief Получить время создания файла
        /// @param p путь до файла
        /// @return 
        filesystem::file_time_type create_time(const filesystem::path &p);
        filesystem::file_time_type create_time(const filesystem::path &p, FilesystemErrors &ec) noexcept;

        /// @brief Получить время последнего 
        /// @param p 
        /// @return 
        filesystem::file_time_type last_acess_time(const filesystem::path &p);
        filesystem::file_time_type last_acess_time(const filesystem::path &p, FilesystemErrors &ec) noexcept;

        /// @brief Получить атрибуты файла
        /// @param p пуйть до файла
        /// @return
        AttributeMasks get_attr(const path &p);

        /// @brief Получить атрибуты файла
        /// @param p пуйть до файла
        /// @param ec
        /// @return
        AttributeMasks get_attr(const path &p, FilesystemErrors &ec) noexcept;

        /// @brief Удалить файл или пустую папку
        /// @param p путь
        /// @throw код ошибки
        void remove(const path &p);

        /// @brief Удалить файл или пустую папку
        /// @param p путь
        void remove(const path &p, FilesystemErrors &ec) noexcept;

        std::uintmax_t remove_all(const path &p);
        std::uintmax_t remove_all(const path &p, FilesystemErrors &ec);

        bool create_directory(const filesystem::path &p);
        bool create_directory(const filesystem::path &p, FilesystemErrors &ec) noexcept;
        bool create_directory( const filesystem::path& p, const filesystem::path& existing_p );
        bool create_directories( const filesystem::path& p );
        bool create_directories( const filesystem::path& p, FilesystemErrors& ec );

        path temp_directory_path();
    } // namespace filesystem

    
} // namespace KolibriLib

#endif // __FILESYSTEM_H__