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
        class Path
        {
            public:
                Path(std::string path = "/");
                /// @brief Получить char* строку
                /// @return Функция возвращает конвертированную строку @link _string
                char* GetChars() const;

                /// @brief Получить строку
                /// @return Функция возвращает @link _string
                std::string GetString() const;
                
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
        /// @param name имя файла
        /// @return Значение из списка @link Errors
        int CreateFile(const Path& name);

        /// @brief удалить файл  или папку
        /// @param name имя файла
        /// @return Значение из списка @link Errors
        int Delete(const Path& name);
        
        /// @brief Создать папку
        /// @param path путь
        /// @return Значение из списка @link Errors
        int MakeDirectory(const Path& path);

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool Exist(const Path& Path);

        /// @brief Переименовать файл
        /// @param OldName старое имя файла
        /// @param NewName новое имя файла
        /// @return  Значение из списка @link Errors
        /// @paragraph Аналог mv. Имена файлов - это полные пути
        int Rename(const Path& OldName, const Path& NewName);

        
    }
} // namespace KolibriLib



#endif // __FILESYSTEM_H__