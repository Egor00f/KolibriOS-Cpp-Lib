#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__



#include <string>
#include <sys/ksys.h>
#include <string.h>
#include <stdlib.h>



namespace KolibriLib
{
    /// @brief Работа с файлами
    /// @paragraph Это пространство имён этакий аналог стандартной библиотеки <filesystem> 
    namespace filesystem
    {

        /// @brief Файловый путь
        class Path
        {
            public:
                Path(std::string path);
<<<<<<< Updated upstream

=======
                Path(char* path);
                /// @brief Получить char* строку
                /// @return Функция возвращает конвертированную строку @link _string
>>>>>>> Stashed changes
                const char* GetChars() const;

                /// @brief Получить строку
                /// @return Функция возвращает @link _string
                std::string GetString() const;

                Path& operator / (const Path& a);
                Path& operator / (const std::string& a);

                bool operator == (const Path& a) const;
                bool operator != (const Path &a) const;

            private:
                std::string _string;
        };


        /// @brief Список ошибок файловой системы
        enum Errors
        {
            /// @brief успешно
            Successfully = 0,
            /// @brief функция не поддерживается для данной файловой системы
            NotSupport = 2,
            /// @brief неизвестная файловая система
            UnklownFileSystem = 3,
            /// @brief файл не найден
            NotFound = 5,
            /// @brief файл закончился
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

        /// @brief Создать файл
        /// @param name полный путь до файла
        /// @return
        int CreateFile(const char *name);

        /// @brief Создать файл
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int CreateFile(const char *name, char *path);

        /// @brief Создать файл
        /// @param name имя файла
        /// @return
        int CreateFile(const Path& name);

        /// @brief Создать файл
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int CreateFile(const std::string& name, const Path& path);

        /// @brief удалить файл или папку
        /// @param name полный путь до файла
        /// @return
        int Delete(const char *name);

        /// @brief удалить файл или папку
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int Delete(const char *name, char *path);
        
        /// @brief удалить файл  или папку
        /// @param name имя файла
        /// @return
        int Delete(const Path& name);

        /// @brief удалить файл или папку
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int Delete(const std::string &name, const Path& path);

        /// @brief Создать папку
        /// @param path путь
        /// @return
        int MakeDirectory(const char *path);

        /// @brief Создать папку
        /// @param path путь
        /// @return
        int MakeDirectory(const Path& path);

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool Exist(const Path& Path);

        int Rename(const Path& OldName, const Path& NewName);

<<<<<<< Updated upstream
        Path::Path(std::string path)
        {
            _string = path;
        }

        const char *Path::GetChars() const
        {
            return _string.c_str();
        }

        std::string Path::GetString() const
        {
            return _string;
        }

        Path &Path::operator/(const Path &a)
        {
            _string += a._string;

            return *this;
        }

        int CreateFile(const char *name)
        {
            return _ksys_file_create(name);
        }

        int CreateFile(const char *name, char *path)
        {
            strcat(path, name);
            int ret = _ksys_file_create(path);
            return ret;
        }

        int CreateFile(const Path &name)
        {
            return _ksys_file_create(name.GetChars());
        }

        int CreateFile(const std::string &name, const Path &path)
        {
            std::string fullPath = path.GetString() + name;
            return _ksys_file_create(fullPath.c_str());
        }

        int Delete(const char *name)
        {
            return _ksys_file_delete(name);
        }

        int Delete(const char *name, char *path)
        {
            strcat(path, name);
            return _ksys_file_delete(path);
        }

        int Delete(const Path &name)
        {
            return _ksys_file_delete(name.GetChars());
        }

        int Delete(const std::string &name, const Path &path)
        {
            std::string fullPath = path.GetString() + name;
            return _ksys_file_delete(fullPath.c_str());
        }

        int MakeDirectory(const char *path)
        {
            return _ksys_mkdir(path);
        }

        int MakeDirectory(const Path &path)
        {
            return _ksys_mkdir(path.GetChars());
        }

        bool Exist(const Path &Path)
        {
            ksys_bdfe_t *buff;
            if (_ksys_file_info(Path.GetChars(), buff) > 0)
            {
                return true;
            }
            return false;
        }

        int Rename(const Path &OldName, const Path &NewName)
        {
            return _ksys_file_rename(OldName.GetChars(), NewName.GetChars());
        }
=======
        
>>>>>>> Stashed changes
    }
} // namespace KolibriLib



#endif // __FILESYSTEM_H__