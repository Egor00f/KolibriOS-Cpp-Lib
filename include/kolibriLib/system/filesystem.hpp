#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__


#include <sys/ksys.h>

#include <string>

namespace KolibriLib
{
    /// @brief Работа с файлами
    /// @paragraph Это пространство имён этакий аналог стандартной библиотеки <filesystem> 
    namespace filesystem
    {

        /// @brief Путь до файла/папки
        /// @paragraph Полность совместим с std::string
        class Path
        {
            public:
                Path(const std::string& path = "/");
                /// @brief Получить char* строку
                /// @return Функция возвращает конвертированную строку @link _string
                const char* GetChars() const;

                /// @brief Получить строку
                /// @return Функция возвращает @link _string
                const std::string& GetString() const;
                
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

        /// @brief Создать файл
        /// @param name имя файла
        /// @return Значение из списка @link Errors
        inline int CreateFile(const Path &name)
        {
            return _ksys_file_create(name.GetChars());
        }

        /// @brief удалить файл  или папку
        /// @param name имя файла
        /// @return Значение из списка @link Errors
        inline int Delete(const Path &name)
        {
            return _ksys_file_delete(name.GetChars());
        }

        /// @brief Создать папку
        /// @param path путь
        /// @return Значение из списка @link Errors
        inline int MakeDirectory(const Path &path)
        {
            return _ksys_mkdir(path.GetChars());
        }

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        inline bool Exist(const Path &Path)
        {
            ksys_bdfe_t *buff = new ksys_bdfe_t;
            int a = _ksys_file_info(Path.GetChars(), buff);
            delete buff;
            return a > 0;
        }

        /// @brief Переименовать файл
        /// @param OldName старое имя файла
        /// @param NewName новое имя файла
        /// @return  Значение из списка @link Errors
        /// @paragraph Аналог mv. Имена файлов - это полные пути
        inline int Rename(const Path &OldName, const Path &NewName)
        {
            return _ksys_file_rename(OldName.GetChars(), NewName.GetChars());
        }
        

    } // namespace filesystem

    
} // namespace KolibriLib



#endif // __FILESYSTEM_H__