#pragma once
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
        int CreateFile(const std::string& name);

        /// @brief Создать файл
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int CreateFile(const std::string& name, const std::string& path);

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
        int Delete(const std::string& name);

        /// @brief удалить файл или папку
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int Delete(const std::string &name, const std::string& path);

        /// @brief Создать папку
        /// @param path путь
        /// @return
        int MakeDirectory(const char *path);

        /// @brief Создать папку
        /// @param path путь
        /// @return
        int MakeDirectory(const std::string& path);

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool Exist(const std::string& Path);

        int Rename(const std::string& OldName, const std::string& NewName);
        

    }
} // namespace KolibriLib



#endif // __FILESYSTEM_H__