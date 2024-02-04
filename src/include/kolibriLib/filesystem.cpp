#include "filesystem.hpp"

int KolibriLib::filesystem::CreateFile(const char *name)
{
    return _ksys_file_create(name);
}

int KolibriLib::filesystem::CreateFile(const char *name, char *path)
{
    strcat(path, name);
    int ret = _ksys_file_create(path);
    return ret;
}

int KolibriLib::filesystem::CreateFile(const std::string& name)
{
    return _ksys_file_create(name.c_str());
}

int KolibriLib::filesystem::CreateFile(const std::string& name, const std::string& path)
{
    std::string fullPath = path + name;
    return _ksys_file_create(fullPath.c_str());
}

int KolibriLib::filesystem::Delete(const char *name)
{
    return _ksys_file_delete(name);
}

int KolibriLib::filesystem::Delete(const char *name, char *path)
{
    strcat(path, name);
    return _ksys_file_delete(path);
}

int KolibriLib::filesystem::Delete(const std::string& name)
{
    return _ksys_file_delete(name.c_str());
}

int KolibriLib::filesystem::Delete(const std::string& name, const std::string& path)
{
    std::string fullPath = path + name;
    return _ksys_file_delete(fullPath.c_str());
}

int KolibriLib::filesystem::MakeDirectory(const char *path)
{
    return _ksys_mkdir(path);
}

int KolibriLib::filesystem::MakeDirectory(const std::string& path)
{
    return _ksys_mkdir(path.c_str());
}

bool KolibriLib::filesystem::Exist(const std::string& Path)
{
    ksys_bdfe_t *buff;
    if (_ksys_file_info(Path.c_str(), buff) > 0)
    {
        return true;
    }
    return false;
}

int KolibriLib::filesystem::Rename(const std::string& OldName, const std::string& NewName)
{
    return _ksys_file_rename(OldName.c_str(), NewName.c_str());
}