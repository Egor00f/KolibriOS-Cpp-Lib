#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__


#include <include_ksys.h>

#include <string>
#include <system_error>
#include <chrono>
#include <ctime>

#include "types.hpp"
#include "config.hpp"
#include "file_status.hpp"


namespace KolibriLib
{
    /// @brief Работа с файлами
    /// @paragraph подражает std::filesystem из C++17
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
                /// @brief Конструктор
                /// @param path Путь
                Path(const char* path = "/");

                /// @brief Конструктор
                /// @param path путь
                Path(const std::string& path);

                Path(const Path& p) = default;

                /// @brief Длинна строки
                std::size_t length() const;

                operator const char*() const;
                operator std::string() const;
                
                Path &operator / (const Path &a);
                Path &operator / (const std::string &a);
                Path &operator + (const Path &a);
                Path &operator + (const std::string &a);
                Path &operator = (const Path &a);
                Path &operator = (const std::string &a);

                bool operator == (const Path &a) const;
                bool operator != (const Path &a) const;

                bool operator == (const std::string &a) const;
                bool operator != (const std::string &a) const;
            private:
                std::string _string;
        };

        /// @brief Штоб название было как в std::filesystem, а то менять в куче файлов название не очень
        typedef Path path;

        

        /// @brief Список ошибок файловой системы
        class filesystem_error
        {
        public:

        filesystem_error& operator=( const filesystem_error& other );

        filesystem_error& operator=( const int& other );

        const int& code() const;

        private:
            int _code;
        };

        using file_time_type = std::chrono::time_point<FileTimeAndDate>;

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
            directory_entry( const filesystem::path& p, std::error_code& ec );

            ~directory_entry() = default;

            void assign( const filesystem::path& p );
            void assign( const filesystem::path& p, std::error_code& ec );

            void replace_filename( const filesystem::path& p );
            void replace_filename( const filesystem::path& p, std::error_code& ec );

            void refresh();
            void refresh( std::error_code& ec ) noexcept;

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
        std::uintmax_t file_size(const Path &p, std::error_code& ec ) noexcept;

        /// @brief 
        /// @param p 
        /// @param new_size 
        void resize_file(const path &p, std::uintmax_t new_size);

        /// @brief 
        /// @param p 
        /// @param new_size 
        /// @param ec
        void resize_file(const filesystem::path &p, std::uintmax_t new_size, std::error_code &ec) noexcept;

        bool copy_file(const filesystem::path &from, const filesystem::path &to);
        bool copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options);
        bool copy_file(const filesystem::path &from, const filesystem::path &to, filesystem::copy_options options, std::error_code &ec);

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool exists(const Path &p);
        bool exists(const filesystem::path &p, std::error_code &ec) noexcept;

        void rename(const filesystem::path &old_p, const filesystem::path &new_p);
        void rename( const filesystem::path& old_p, const filesystem::path& new_p, std::error_code& ec ) noexcept;

        bool is_regular_file( filesystem::file_status s ) noexcept;
        bool is_regular_file( const filesystem::path& p );
        bool is_regular_file( const filesystem::path& p, std::error_code& ec ) noexcept;

        bool is_directory( filesystem::file_status s ) noexcept;
        bool is_directory(const filesystem::path &p);
        bool is_directory( const filesystem::path& p, std::error_code& ec ) noexcept;

        filesystem::file_time_type last_write_time( const filesystem::path& p );
        filesystem::file_time_type last_write_time(const filesystem::path &p, std::error_code &ec) noexcept;

        filesystem::file_time_type create_time(const filesystem::path &p);
        filesystem::file_time_type create_time(const filesystem::path &p, std::error_code &ec) noexcept;

        filesystem::file_time_type last_acess_time(const filesystem::path &p);
        filesystem::file_time_type create_acess_time(const filesystem::path &p, std::error_code &ec) noexcept;
    } // namespace filesystem

    
} // namespace KolibriLib



#endif // __FILESYSTEM_H__