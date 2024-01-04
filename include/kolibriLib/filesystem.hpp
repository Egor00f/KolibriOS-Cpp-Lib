#pragma once
#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__



#include <string>
extern "C"
{
    #include <sys/ksys.h>
    #include <string.h>
    #include <stdlib.h>
}

namespace KolibriLib
{
    namespace filesystem
    {
        /// @brief Создать файл
        /// @param name полный путь до файла
        /// @return
        int CreateFile(const char *name)
        {
            return _ksys_file_create(name);
        }
        /// @brief Создать файл
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int CreateFile(const char *name, char *path)
        {
            strcat(path, name);
            int ret = _ksys_file_create(path);
            return ret;
        }
        /// @brief Создать файл
        /// @param name имя файла
        /// @return
        int CreateFile(std::string name)
        {
            return _ksys_file_create(name.c_str());
        }
        /// @brief Создать файл
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int CreateFile(std::string name, std::string path)
        {
            std::string fullPath = path + name;
            return _ksys_file_create(fullPath.c_str());
        }


        /// @brief удалить файл или папку
        /// @param name полный путь до файла
        /// @return
        int Delete(const char *name)
        {
            return _ksys_file_delete(name);
        }
        /// @brief удалить файл или папку
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int Delete(const char *name, char *path)
        {
            strcat(path, name);
            return _ksys_file_delete(path);
        }
        /// @brief удалить файл  или папку
        /// @param name имя файла
        /// @return
        int Delete(std::string name)
        {
            return _ksys_file_delete(name.c_str());
        }
        /// @brief удалить файл или папку
        /// @param name имя файла
        /// @param path путь до файла
        /// @return
        int Delete(std::string name, std::string path)
        {
            std::string fullPath = path + name;
            return _ksys_file_delete(fullPath.c_str());
        }



        /// @brief Создать папку
        /// @param path путь
        /// @return
        int mkdir(const char *path)
        {
            return _ksys_mkdir(path);
        }
        /// @brief Создать папку
        /// @param path путь
        /// @return
        int mkdir(std::string path)
        {
            return _ksys_mkdir(path.c_str());
        }

        /// @brief проверяет существует ли файл или папки
        /// @param путь до файла/папки
        /// @return true если файл или папка существует, иначе false
        bool Exist(std::string Path)
        {
            ksys_bdfe_t *buff;
            if(_ksys_file_info(Path.c_str(), buff) > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        int Rename(std::string OldName, std::string NewName)
        {
            return _ksys_file_rename(OldName.c_str(), NewName.c_str());
        }
        

    }
} // namespace KolibriLib



#endif // __FILESYSTEM_H__