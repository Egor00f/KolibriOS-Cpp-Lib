#include "filesystem.hpp"

using namespace KolibriLib;
using namespace filesystem;


Path::Path(std::string path)
{
    _string = path;
}

Path::Path(char* path)
{
    _string = path;
}

const char *Path::GetChars() const
{
    return _string.c_str();
}

std::string KolibriLib::filesystem::Path::GetString() const
{
    return _string;
}

Path &Path::operator/(const Path &a)
{
    _string += a._string;

    return *this;
}

Path &KolibriLib::filesystem::Path::operator/(const std::string &a)
{
    _string += a;
    return *this;
}

bool KolibriLib::filesystem::Path::operator==(const Path &a) const
{
    return _string == a._string;
}

bool KolibriLib::filesystem::Path::operator!=(const Path &a) const
{
    return _string != a._string;
}

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

int KolibriLib::filesystem::CreateFile(const Path &name)
{
    return _ksys_file_create(name.GetChars());
}

int KolibriLib::filesystem::CreateFile(const std::string &name, const Path &path)
{
    std::string fullPath = path.GetString() + name;
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

int KolibriLib::filesystem::Delete(const Path &name)
{
    return _ksys_file_delete(name.GetChars());
}

int KolibriLib::filesystem::Delete(const std::string &name, const Path &path)
{
    std::string fullPath = path.GetString() + name;
    return _ksys_file_delete(fullPath.c_str());
}

int KolibriLib::filesystem::MakeDirectory(const char *path)
{
    return _ksys_mkdir(path);
}

int KolibriLib::filesystem::MakeDirectory(const Path &path)
{
    return _ksys_mkdir(path.GetChars());
}

bool KolibriLib::filesystem::Exist(const Path &Path)
{
    ksys_bdfe_t *buff;
    if (_ksys_file_info(Path.GetChars(), buff) > 0)
    {
        return true;
    }
    return false;
}

int KolibriLib::filesystem::Rename(const Path &OldName, const Path &NewName)
{
    return _ksys_file_rename(OldName.GetChars(), NewName.GetChars());
}