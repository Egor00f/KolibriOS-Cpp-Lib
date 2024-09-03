#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__


#include <sys/ksys.h>

#include <string>
#include <system_error>

#include "config.hpp"
#include "file_status.hpp"


namespace KolibriLib
{
    /// @brief Работа с файлами
    /// @paragraph похоже на std::filesystem
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

        /// @brief Получить размер файла
        /// @param p путь до файла
        /// @return размер файла
        /// @throw static_cast<std::uintmax_t>(-1) в случае ошибки
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
        bool exists(const filesystem::path &p, filesystem_error &ec) noexcept;

        void rename(const filesystem::path &old_p, const filesystem::path &new_p);
        void rename( const filesystem::path& old_p, const filesystem::path& new_p, std::error_code& ec ) noexcept;

        bool is_regular_file( filesystem::file_status s ) noexcept;
        bool is_regular_file( const filesystem::path& p );
        bool is_regular_file( const filesystem::path& p, std::error_code& ec ) noexcept;
    } // namespace filesystem

    
} // namespace KolibriLib



#endif // __FILESYSTEM_H__